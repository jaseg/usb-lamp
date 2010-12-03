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

#include "statestruct.h"

void init_pwm(void);
void enable_timer2(void);
void disable_timer2(void);
void update_timers(void);
void set_channel(uint8_t channel, uint16_t value);
void set_channels(uint16_t c0, uint16_t c1, uint16_t c2);
void clock_init(void);
void transmission_sent(statestruct* state);
//void handle_error(statestruct* state, uint8_t error_code);
//void handle_command(statestruct* state, command* cmd);

#endif//__MAIN_H__