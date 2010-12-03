/* 
* Logarithmic 16-bit pwm 8-bit lookup table
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

#ifndef __GENERATED_PWM_LUT_LOG_8_16__
#define __GENERATED_PWM_LUT_LOG_8_16__

#include <avr/pgmspace.h>

const uint16_t log_pwm_lut[] PROGMEM = {
1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 13, 13, 14, 15, 15, 16, 17, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 32, 33, 35, 36, 38, 40, 41, 43, 45, 47, 49, 52, 54, 56, 59, 61, 64, 67, 70, 73, 76, 79, 83, 87, 91, 95, 99, 103, 108, 112, 117, 123, 128, 134, 140, 146, 152, 159, 166, 173, 181, 189, 197, 206, 215, 225, 235, 245, 256, 267, 279, 292, 304, 318, 332, 347, 362, 378, 395, 412, 431, 450, 470, 490, 512, 535, 558, 583, 609, 636, 664, 693, 724, 756, 790, 825, 861, 899, 939, 981, 1024, 1069, 1117, 1166, 1218, 1272, 1328, 1387, 1448, 1512, 1579, 1649, 1722, 1798, 1878, 1961, 2048, 2139, 2233, 2332, 2435, 2543, 2656, 2774, 2896, 3025, 3158, 3298, 3444, 3597, 3756, 3922, 4096, 4277, 4467, 4664, 4871, 5087, 5312, 5547, 5793, 6049, 6317, 6597, 6889, 7194, 7512, 7845, 8192, 8555, 8933, 9329, 9742, 10173, 10624, 11094, 11585, 12098, 12634, 13193, 13777, 14387, 15024, 15689, 16384, 17109, 17867, 18658, 19484, 20347, 21247, 22188, 23170, 24196, 25268, 26386, 27554, 28774, 30048, 31379, 32768, 34219, 35734, 37316, 38968, 40693, 42495, 44376, 46341, 48393, 50535, 52773, 55109, 57549, 60097, 62757
};

#endif//__GENERATED_PWM_LUT_LOG_8_16__

