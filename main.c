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

/* Notes
 * 
 * PC0 has a high-active led connected to it which signalises errors.
 */

/* RGBulb command overview
 * 
 * Function: 0x00
 * Command: 0x00 Nop/Return (may carry the last command's return value as argument)
 * Command: 0x01 Ping (responds with a Nop to the sender)
 * Command: 0x02 Get channels (response: return 0xRRRRGGGGBBBB (HByte first))
 * Command: 0x03 Set brightness (format: 0xCCVVVV (Channel, Value; HByte first))
 * Command: 0x04 Set channels (format: 0xRRRRGGGGBBBB, same as in "get channels". HByte first)
 * 
 */

#include "buz2.h"
#include <avr/interrupt.h>
#include <stdlib.h>

volatile uint8_t timer0_ovf = 0;
volatile uint8_t timer0_pwm_high = 0;

void handle_command(statestruct* state, command* cmd){
	if(cmd->function == 0x00){ //default device function
		transmission* tmp1 = malloc(sizeof(transmission));
		c16 c0, c1, c2;
		uint8_t* channelbuf = malloc(sizeof(uint8_t)*6);
		switch(cmd->command){
			case 0x00: //nop/return
				//Ignore. We don't send commands on our own.
				break;
			case 0x01: //ping
				tmp1->destination.i16 = cmd->sender;
				tmp1->function = 0x00;
				tmp1->command = 0x00; //return
				tmp1->payload = 0;
				tmp1->payload_length = 0;
				tmp1->retry_count = 0;
				enqueue_transmission(state, tmp1);
				break;
			case 0x02: //get channels
				channelbuf[0]=OCR1AH;
				channelbuf[1]=OCR1AL;
				channelbuf[2]=OCR1BH;
				channelbuf[3]=OCR1BL;
				c16 bval;
				bval.i16 = timer0_pwm_high*OCR2; //Magic! btw, FIXME does this even work? (8bit*8bit->16bit?)
				channelbuf[4]=bval.i8h;
				channelbuf[5]=bval.i8l;
				tmp1->destination.i16 = cmd->sender;
				tmp1->function = 0x00;
				tmp1->command = 0x00; //return
				tmp1->payload = channelbuf;
				tmp1->payload_length = 6;
				tmp1->retry_count = 0;
				enqueue_transmission(state, tmp1);
				break;
			case 0x03: //set brightness/channel
				c1.i8h = cmd->payload[1];
				c1.i8l = cmd->payload[2];
				set_channel(cmd->payload[0], c1.i16);
				break;
			case 0x04: //set channels
				c0.i8h = cmd->payload[0];
				c0.i8l = cmd->payload[1];
				c1.i8h = cmd->payload[2];
				c1.i8l = cmd->payload[3];
				c2.i8h = cmd->payload[4];
				c2.i8l = cmd->payload[5];
				set_channels(c0.i16, c1.i16, c2.i16);
				break;
		}
	}
}

//Two channels of 16-bit PWM are provided by timer 1 hardware, the third channel is hacked together using timer 0 and timer 2.
void init_pwm(){
	//16-bit timer 1
	TCCR1A |= (1<<COM1A1)|(1<<COM1B1)|(1<<WGM11); //Fast PWM, TOP is ICR1, non-inverting PWM mode
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS10); //No prescaling
	TIMSK  |= (1<<TOIE1); //Enable overflow interrupt
	ICR1    = 0xFFFF; //Set TOP
	DDRB   |= 0x06; //Set two output pins (PB1, PB2)
	//8-bit timer 0
	TCCR0  |= (1<<CS02); //Prescaler 256 (one timer 2 overflow)
	TIMSK  |= (1<<TOIE0); //Enable overflow interrupt
	
	//8-bit timer 2
	TCCR2  |= (1<<WGM20)|(1<<WGM21)|(1<<COM21); //Fast PWM, non-inverting mode
	
	DDRB   |= 0x08; //Set third output pin (PB3)
	PORTB  &=~0x08; //Unset the port bit
	
	//sync timers
	update_timers();
}

void enable_timer2(){
	TCCR2 |= (1<<CS20);
}

void disable_timer2(){
	TCCR2 &= ~(1<<CS20);
}

ISR(TIMER0_OVF_vect){
	timer0_ovf++;
	if(timer0_ovf == timer0_pwm_high){
		enable_timer2();
	}
	if(timer0_ovf == 0){
		disable_timer2();
	}
}

void update_timers(){
	TCNT0 = 0;
	TCNT1 = 0;
	TCNT2 = 0;
}

void set_channel(uint8_t channel, uint16_t value){
	c16 tmp;
	switch(channel){
		case 0:
			OCR1A = value;
			break;
		case 1:
			OCR1B = value;
			break;
		case 2:
			tmp.i16 = value;
			OCR2 = tmp.i8l;
			timer0_pwm_high = tmp.i8h;
			break;
	}
	update_timers();
}

void set_channels(uint16_t c0, uint16_t c1, uint16_t c2){
	//channel 0
	OCR1A = c0;
	//channel 1
	OCR1B = c1;
	//channel 2
	c16 tmp;
	tmp.i16 = c2;
	OCR2 = tmp.i8l;
	timer0_pwm_high = tmp.i8h;
	//update.
	update_timers();
}

int main(void){
	//Well, eh, do something cool!
	DDRC |= 0x01;
	statestruct* state = init_state();
	init_pwm();
	while(1){
		transition(state);
	}
}
