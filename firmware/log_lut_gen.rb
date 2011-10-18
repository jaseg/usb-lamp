#!/usr/bin/env ruby

inbits = 12
outbits = 16
gamma = 2.2

puts <<eos
/* 
* #{outbits}-bit pwm #{inbits}-bit gamma correction lookup table with
* gamma=#{gamma}
* 
* Copyright 2010 by Jan Sebastian Götte (s@twopi.eu)
*  - - - - - - - - - - - - LICENSE INFORMATION - - - - - - - - - - - -
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
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

#ifndef __GENERATED_PWM_LUT_LOG_#{inbits}_#{outbits}_#{gamma}__
#define __GENERATED_PWM_LUT_LOG_#{inbits}_#{outbits}_#{gamma}__

#include <avr/pgmspace.h>

const uint16_t log_pwm_lut[] PROGMEM = {
#{(0...2**inbits).map {|i| ((2**outbits)*((i/(2**inbits.to_f))**(gamma))).round }.join(", ")}
};

#endif//__GENERATED_PWM_LUT_LOG_#{inbits}_#{outbits}_#{gamma}__

eos
