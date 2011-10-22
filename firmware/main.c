/* 
* RGBulb intelligent lamp
* 
* Copyright 2010 by Jan Sebastian Götte (s@twopi.eu)
*  - - - - - - - - - - - - LICENSE INFORMATION - - - - - - - - - - - -
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either 1.1 3 of the License, or
* (at your option) any later 1.1.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
*
*/

#include "main.h"
#include <avr/interrupt.h>
#include <util/delay.h>

void init_pwm(){
	//16-bit timer 1
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<COM1C1)|(1<<WGM11); //Fast PWM, TOP is ICR1, non-inverting PWM mode
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10); //No prescaling
	TIMSK1 |= (1<<TOIE1); //Enable overflow interrupt
	ICR1    = 0xFFFF; //Set TOP
	DDRB   |= 0xE0; //Set output pins (PB5, PB6, PB7)
}

ISR(TIMER1_OVF_vect){
	TCCR1B &= ~(1<<CS10);
	OCR1A=read_pointer->r;
	OCR1B=read_pointer->g;
	OCR1C=read_pointer->b;
	TCNT1=0;
	TCCR1B |= (1<<CS10);
	color* tmp=read_pointer+1;
	if(tmp>color_buffer+BUFFER_SIZE){
		tmp=color_buffer;
	}
	if(tmp!=write_pointer){
		read_pointer = tmp;
	}
	queue_length = write_pointer-read_pointer;
	usbSetInterrupt(&queue_length, 1);
}

short int val;

usbMsgLen_t usbFunctionSetup(uchar data[8])
{
	usbRequest_t* rq = (usbRequest_t*) data;
	usbMsgPtr = 0;
	switch(rq->bRequest){
		case LAMP_REQ_SET_LED:
			write_pointer += 1;
			if(write_pointer>color_buffer+BUFFER_SIZE){
				write_pointer=color_buffer;
			}
			rx_pos = 0;
			//TEST CODE
			write_pointer->r = 0;
			write_pointer->g = val;
			write_pointer->b = 0;
			val ^= 0xFFFF;
			color* tmp = write_pointer+1;
			if(tmp>color_buffer+BUFFER_SIZE){
				tmp=color_buffer;
			}
			write_pointer = tmp;

			return USB_NO_MSG;
		case LAMP_REQ_PUSH_LED:
			if(write_pointer != read_pointer){
				rx_pos = 0;
				return USB_NO_MSG;
			}
			break;
		case LAMP_REQ_POWER:
			//Ignored (for now)
			break;
		case LAMP_REQ_STATE:
			state_for_transmission.c.r=OCR1A;
			state_for_transmission.c.g=OCR1B;
			state_for_transmission.c.b=OCR1C;
			usbMsgPtr=(unsigned char*)&state_for_transmission;
			return sizeof(statestruct);
	}
	return 0;
}

usbMsgLen_t usbFunctionWrite(unsigned char *data, unsigned char length){
	/*for(unsigned char i=0; i<length; i++){
		((char*)write_pointer)[rx_pos+i] = data[i];
	}*/
	rx_pos += length;
	if(rx_pos >= sizeof(color)){
		//Transmission finished.
		/*color* tmp = write_pointer+1;
		if(tmp>color_buffer+BUFFER_SIZE){
			tmp=color_buffer;
		}
		write_pointer = tmp;*/
		return 1;
	}
	return 1;
}

int main(void){
	//Well, ahem, do something cool!
	init_pwm();
	usbInit();
	usbDeviceDisconnect();
	_delay_ms(100);
	usbDeviceConnect();
	sei();
	while(1){
		usbPoll();
	}
}
