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

#ifndef __MAIN_H__
#define __MAIN_H__
#include <avr/io.h>
//#include "pwm_log_lut.h"
#include "../requests.h" //TODO bad style.
#include "usbdrv.h"

#define BUFFER_SIZE	32

void init_pwm(void);
void set_channels_direct(uint16_t c0, uint16_t c1, uint16_t c2);

typedef struct {
	uint16_t r;
	uint16_t g;
	uint16_t b;
} precision_color;

precision_color color_buffer[BUFFER_SIZE];
precision_color* read_pointer=color_buffer;
precision_color* write_pointer=color_buffer;
uint8_t queue_length;

typedef union {
	uint16_t i16;
	struct {
		uint8_t i8l;
		uint8_t i8h;
	};
} c16;

#endif//__MAIN_H__
