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
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include <string.h>

#include "opendevice.h"
#include "../requests.h" //TODO relative path: not so nice.

#define GAMMA 2.2F
#define CYCLES_PER_SECOND 16000000.0F/65536

typedef struct {
	unsigned short r, g, b;
} color;

int push_color(usb_dev_handle* rgbulb, color c){
	int ec = 0;
	if((ec = usb_control_msg(rgbulb, 0x40, LAMP_REQ_SET_LED, c.r, c.g, 0, c.b, 1000))){
		printf("Cannot light lamp (error code %d).\n", ec);
		return 1;
	}
	return 0;
}

color get_color(usb_dev_handle* rgbulb){
	statestruct state;
	int ec = 0;
	if((ec = usb_control_msg(rgbulb, 0x40, LAMP_REQ_STATE, 0, 0, (char*)&state, sizeof(statestruct), 1000))){
		printf("Cannot get lamp (error code %d).\n", ec);
		return (color) {0, 0, 0};
	}
	return (color) {state.r, state.g, state.b};
}

short get_queue_length(usb_dev_handle* rgbulb){
	unsigned char queue_length = 0;
	int ec = 0;
	if((ec = usb_interrupt_read(rgbulb, 1, (char*)&queue_length, 1, 1000))){
		printf("Cannot read lamp value queue interrupt. NOTE: The developer does not yet know whether this is normal (FIXME) (error code %d).\n", ec);
		return -1;
	}
	return queue_length;
}

void usage(){
	printf("Usage: rgbulb [-f speed] r g b\n(where r, g and b are values between 0 and 65535)\n");
}

int main(int argc, char** argv)
{
	usb_dev_handle* rgbulb;
	usb_init();
	int ec = 0;
	if((ec = usbOpenDevice(&rgbulb, 0x16c0, "s@jaseg.de", 0x05dc, "RGBulb", "*", 0, stdout))){ //Ugh. Double reference.
		printf("Cannot open device handle (error code %d).\n", ec);
		return 2;
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
	color dstcolor = {0, 0, 0};
	char* endptr = 0;
	for(int i=0; i<3; i++){
		unsigned long int val = strtoul(argv[argc-i], &endptr, 0);
		if(endptr){
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
		push_color(rgbulb, dstcolor);
	}else{
		if(argc != 6){
			usage();
			exit(1);
		}
		color start_color = get_color(rgbulb);
		char* endptr=0;
		float speed = strtof(argv[2], &endptr);
		if(endptr){
			printf("Cannot parse number format.\n");
			usage();
			exit(1);
		}
		for(float position = 0; position < 1.0F; position += CYCLES_PER_SECOND/speed){
			//Magick of Color and Gamma
			//(Not sure this works...)
			color new_color = {
				(unsigned short)round(start_color.r + ((dstcolor.r - start_color.r)*pow(position, GAMMA))),
				(unsigned short)round(start_color.g + ((dstcolor.g - start_color.g)*pow(position, GAMMA))),
				(unsigned short)round(start_color.b + ((dstcolor.b - start_color.b)*pow(position, GAMMA))),
			};
			push_color(rgbulb, new_color);
		}
	}
	usb_close(rgbulb);
	return 0;
}

