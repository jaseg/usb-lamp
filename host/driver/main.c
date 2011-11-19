/* 	Penta host implementation
	Copyright (C) 2011 by Sebastian Götte <s@jaseg.de>

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Error handling parts blatantly ripped from libusb0.1.12.
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#include "opendevice.h"
#include "../../requests.h" //TODO relative path: not so nice.

#define GAMMA 2.2F
#define F_CPU 16000000 //NOTE: always sync this with the firmware's makefile and the hardware's reality
#define CYCLES_PER_SECOND F_CPU/65536.0F


char rgbulb_error_str[256];
#define RGBULB_ERROR_STR(x, format, args...) \
	do { \
	  snprintf(rgbulb_error_str, sizeof(rgbulb_error_str) - 1, format, ## args); \
	  return x; \
	} while (0)

int rgbulb_init(usb_dev_handle** rgbulb){
	usb_init();
	int ec = 0;
	if((ec = usbOpenDevice(rgbulb, 0x16c0, "s@jaseg.de", 0x05dc, "RGBulb", "*", 0, stdout))){
		RGBULB_ERROR_STR(2, "Cannot open device handle (error code %d).", ec);
	}
	return 0;
}

void rgbulb_close(usb_dev_handle* rgbulb){
	usb_close(rgbulb);
}

int set_color(usb_dev_handle* rgbulb, color c){
	int ec = 0;
	char testcolor[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
	if((ec = usb_control_msg(rgbulb, 0x40, LAMP_REQ_SET_LED, 0, 0, testcolor, 6, 1000))){ //(char*)&c, sizeof(color), 1000))){
		RGBULB_ERROR_STR(1, "Cannot light lamp (error code %d: %s).", ec, usb_strerror());
	}
	return 0;
}

int push_color(usb_dev_handle* rgbulb, color c){
	int ec = 0;
	if((ec = usb_control_msg(rgbulb, 0x40, LAMP_REQ_PUSH_LED, 0, 0, (char*)&c, sizeof(color), 1000))){
		RGBULB_ERROR_STR(1, "Cannot light lamp (error code %d: %s).", ec, usb_strerror());
	}
	return 0;
}

color convert_from_float(float r, float g, float b){
	color c={(unsigned short)round(65535*pow(r, GAMMA)),
			 (unsigned short)round(65535*pow(g, GAMMA)),
			 (unsigned short)round(65535*pow(b, GAMMA))};
	return c;
}

color convert_from_char(unsigned char r, unsigned char g, unsigned char b){
	return convert_from_float(r/255.0F, g/255.0F, b/255.0F);
}

color get_color(usb_dev_handle* rgbulb){
	statestruct state;
	int ec = 0;
	if((ec = usb_control_msg(rgbulb, 0x40, LAMP_REQ_STATE, 0, 0, (char*)&state, sizeof(statestruct), 1000))){
		color c = {0, 0, 0};
		RGBULB_ERROR_STR(c, "Cannot get lamp (error code %d: %s).", ec, usb_strerror());
	}
	return (color) {state.c.r, state.c.g, state.c.b};
}

//returns -1 on error, the queue length on success or 0 if no data is available.
short get_queue_length(usb_dev_handle* rgbulb){
	unsigned char queue_length = 0;
	int ec = 0;
	if((ec = usb_interrupt_read(rgbulb, 1, (char*)&queue_length, 1, 1000)) < 0){
		RGBULB_ERROR_STR(-1, "Cannot read lamp value queue interrupt. NOTE: The developer does not yet know whether this is normal (FIXME) (error code %d).", ec);
	}
	return queue_length;
}

int fade(usb_dev_handle* rgbulb, color dstcolor, float speed){
	color start_color = get_color(rgbulb);
	for(float position = 0; position < 1.0F; position += CYCLES_PER_SECOND/speed){
		//Magick of Color and Gamma
		//(Not sure this works...)
		color new_color = {
			(unsigned short)round(start_color.r + ((dstcolor.r - start_color.r)*pow(position, GAMMA))),
			(unsigned short)round(start_color.g + ((dstcolor.g - start_color.g)*pow(position, GAMMA))),
			(unsigned short)round(start_color.b + ((dstcolor.b - start_color.b)*pow(position, GAMMA))),
		};
		push_color(rgbulb, new_color);
		for(;;){
			int ec;
			if((ec = get_queue_length(rgbulb)) < 0){ //the endpoint number 1 is just guessed.
				RGBULB_ERROR_STR(23, "Interrupt read error. Error code %d, error string %s.", ec, usb_strerror());
			}
			if(ec > 0 && ec < 10){
				break;
			}
			usleep(1000);
		}
	}
	return 0;
}

void usage(){
	printf("Usage: rgbulb [-f speed] r g b\n(where r, g and b are values between 0 and 65535)\n");
}

int main(int argc, char** argv)
{
	usb_dev_handle* rgbulb = 0;
	if(rgbulb_init(&rgbulb)){
		printf("%s\n", rgbulb_error_str);
		exit(9);
	}
	if(argc == 2){
		if(strcmp(argv[1], "-h") == 0){
			usage();
			exit(0);
		}else{
			usage();
			exit(2);
		}
	}
	if(argc < 4){
			usage();
			exit(2);
	}
	color start = get_color(rgbulb);
	printf("%s\n", rgbulb_error_str);
	color dstcolor = {0, 0, 0};
	char* endptr = 0;
	for(int i=1; i<4; i++){
		unsigned long int val = strtoul(argv[argc-i], &endptr, 0);
		if(*endptr != '\0'){
			printf("Cannot parse number format.\n");
			usage();
			exit(2);
		} else if(val > 0xFFFF){
			printf("Color value too large.\n");
			usage();
			exit(2);
		}else if(val < 0){
			printf("Color value too small.\n");
			usage();
			exit(2);
		}
		switch(i){
			case 0:
				dstcolor.r=val;
				break;
			case 1:
				dstcolor.g=val;
				break;
			case 2:
				dstcolor.b=val;
				break;
		}
	}
	if(strcmp(argv[1], "-f")){
		//No fading.
		if(argc != 4){
			usage();
			exit(1);
		}
		if(set_color(rgbulb, dstcolor)){
			printf("%s\n", rgbulb_error_str);
		}
	}else{
		if(argc != 6){
			usage();
			exit(1);
		}
		char* endptr=0;
		float speed = strtof(argv[2], &endptr);
		if(*endptr != '\0'){
			printf("Cannot parse number format.\n");
			usage();
			exit(1);
		}
		if(fade(rgbulb, dstcolor, speed)){
			printf("%s\n", rgbulb_error_str);
		}
	}
	rgbulb_close(rgbulb);
	return 0;
}
