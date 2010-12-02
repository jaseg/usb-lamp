/* 
 * SoftPWM study
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

/* This file does only contain schematic "notes"
 */

c16 pwm_values[3];

void init_pwm(){
	
}

void pwm_periodic(){
	
}

ISR(TIMER1_COMP_A_vect){
timer1_comp_a_vect:		LD r24, Z+
						IJMP
}

	
	IJMP 

void set_channel(uint8_t channel, uint16_t value){
	pwm_values[channel].i16 = value;
}

void set_channels(uint16_t ch0, uint16_t ch1, uint16_t ch2){
	pwm_values[0].i16 = ch0;
	pwm_values[1].i16 = ch1;
	pwm_values[2].i16 = ch2;
}

uint16_t get_channel(uint8_t channel){
	return pwm_values[channel];
}


