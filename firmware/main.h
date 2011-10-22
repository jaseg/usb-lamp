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

color color_buffer[BUFFER_SIZE];
color* read_pointer=color_buffer;
color* write_pointer=color_buffer;
volatile statestruct state_for_transmission = {1, {0, 0, 0}};
unsigned char rx_pos;
unsigned char queue_length;

#endif//__MAIN_H__
