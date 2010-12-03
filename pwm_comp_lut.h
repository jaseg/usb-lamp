/* 
* Logarithmic composite pwm 8-bit lookup table
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

#ifndef __GENERATED_PWM_LUT_LOG_COMP_8__
#define __GENERATED_PWM_LUT_LOG_COMP_8__

#include <avr/pgmspace.h>

#ifndef __GENERATED_PWM_LUT_LOG_COMP_PWMPAIR__
#define __GENERATED_PWM_LUT_LOG_COMP_PWMPAIR__
typedef struct {
	uint8_t a;
	uint8_t b;
} pwmpair;
#endif//__GENERATED_PWM_LUT_LOG_COMP_PWMPAIR__

const pwmpair log_pwm_mod_lut[] PROGMEM = {
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{1,1},  	// 1
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{2,1},  	// 2
		{3,1},  	// 3
		{3,1},  	// 3
		{3,1},  	// 3
		{3,1},  	// 3
		{3,1},  	// 3
		{3,1},  	// 3
		{3,1},  	// 3
		{4,1},  	// 4
		{4,1},  	// 4
		{4,1},  	// 4
		{4,1},  	// 4
		{4,1},  	// 4
		{4,1},  	// 4
		{5,1},  	// 5
		{5,1},  	// 5
		{5,1},  	// 5
		{5,1},  	// 5
		{5,1},  	// 5
		{6,1},  	// 6
		{6,1},  	// 6
		{6,1},  	// 6
		{6,1},  	// 6
		{7,1},  	// 7
		{7,1},  	// 7
		{7,1},  	// 7
		{8,1},  	// 8
		{8,1},  	// 8
		{8,1},  	// 8
		{9,1},  	// 9
		{9,1},  	// 9
		{10,1},  	// 10
		{10,1},  	// 10
		{10,1},  	// 10
		{11,1},  	// 11
		{11,1},  	// 11
		{12,1},  	// 12
		{12,1},  	// 12
		{13,1},  	// 13
		{13,1},  	// 13
		{14,1},  	// 14
		{15,1},  	// 15
		{15,1},  	// 15
		{16,1},  	// 16
		{17,1},  	// 17
		{17,1},  	// 17
		{18,1},  	// 18
		{19,1},  	// 19
		{20,1},  	// 20
		{21,1},  	// 21
		{22,1},  	// 22
		{23,1},  	// 23
		{24,1},  	// 24
		{25,1},  	// 25
		{26,1},  	// 26
		{27,1},  	// 27
		{28,1},  	// 28
		{29,1},  	// 29
		{31,1},  	// 31
		{32,1},  	// 32
		{33,1},  	// 33
		{35,1},  	// 35
		{36,1},  	// 36
		{38,1},  	// 38
		{40,1},  	// 40
		{41,1},  	// 41
		{43,1},  	// 43
		{45,1},  	// 45
		{47,1},  	// 47
		{49,1},  	// 49
		{52,1},  	// 52
		{54,1},  	// 54
		{56,1},  	// 56
		{59,1},  	// 59
		{61,1},  	// 61
		{64,1},  	// 64
		{67,1},  	// 67
		{70,1},  	// 70
		{73,1},  	// 73
		{76,1},  	// 76
		{79,1},  	// 79
		{83,1},  	// 83
		{87,1},  	// 87
		{91,1},  	// 91
		{95,1},  	// 95
		{99,1},  	// 99
		{103,1},  	// 103
		{108,1},  	// 108
		{112,1},  	// 112
		{117,1},  	// 117
		{123,1},  	// 123
		{128,1},  	// 128
		{134,1},  	// 134
		{140,1},  	// 140
		{146,1},  	// 146
		{152,1},  	// 152
		{159,1},  	// 159
		{166,1},  	// 166
		{173,1},  	// 173
		{181,1},  	// 181
		{189,1},  	// 189
		{197,1},  	// 197
		{206,1},  	// 206
		{215,1},  	// 215
		{225,1},  	// 225
		{235,1},  	// 235
		{245,1},  	// 245
		{128,2},  	// 256
		{89,3},  	// 267
		{93,3},  	// 279
		{146,2},  	// 292
		{152,2},  	// 304
		{159,2},  	// 318
		{166,2},  	// 332
		{174,2},  	// 348
		{181,2},  	// 362
		{189,2},  	// 378
		{79,5},  	// 395
		{206,2},  	// 412
		{216,2},  	// 432
		{225,2},  	// 450
		{235,2},  	// 470
		{245,2},  	// 490
		{128,4},  	// 512
		{107,5},  	// 535
		{186,3},  	// 558
		{53,11},  	// 583
		{203,3},  	// 609
		{212,3},  	// 636
		{166,4},  	// 664
		{231,3},  	// 693
		{181,4},  	// 724
		{252,3},  	// 756
		{158,5},  	// 790
		{165,5},  	// 825
		{123,7},  	// 861
		{31,29},  	// 899
		{235,4},  	// 940
		{109,9},  	// 981
		{128,8},  	// 1024
		{214,5},  	// 1070
		{86,13},  	// 1118
		{106,11},  	// 1166
		{203,6},  	// 1218
		{212,6},  	// 1272
		{166,8},  	// 1328
		{73,19},  	// 1387
		{181,8},  	// 1448
		{252,6},  	// 1512
		{158,10},  	// 1580
		{97,17},  	// 1649
		{246,7},  	// 1722
		{62,29},  	// 1798
		{235,8},  	// 1880
		{53,37},  	// 1961
		{128,16},  	// 2048
		{93,23},  	// 2139
		{203,11},  	// 2233
		{212,11},  	// 2332
		{203,12},  	// 2436
		{212,12},  	// 2544
		{166,16},  	// 2656
		{146,19},  	// 2774
		{181,16},  	// 2896
		{121,25},  	// 3025
		{243,13},  	// 3159
		{194,17},  	// 3298
		{246,14},  	// 3444
		{109,33},  	// 3597
		{221,17},  	// 3757
		{106,37},  	// 3922
		{128,32},  	// 4096
		{91,47},  	// 4277
		{203,22},  	// 4466
		{212,22},  	// 4664
		{232,21},  	// 4872
		{212,24},  	// 5088
		{166,32},  	// 5312
		{129,43},  	// 5547
		{181,32},  	// 5792
		{242,25},  	// 6050
		{243,26},  	// 6318
		{194,34},  	// 6596
		{83,83},  	// 6889
		{218,33},  	// 7194
		{203,37},  	// 7511
		{212,37},  	// 7844
		{128,64},  	// 8192
		{145,59},  	// 8555
		{203,44},  	// 8932
		{212,44},  	// 9328
		{191,51},  	// 9741
		{185,55},  	// 10175
		{166,64},  	// 10624
		{129,86},  	// 11094
		{181,64},  	// 11584
		{111,109},  	// 12099
		{133,95},  	// 12635
		{167,79},  	// 13193
		{166,83},  	// 13778
		{218,66},  	// 14388
		{181,83},  	// 15023
		{212,74},  	// 15688
		{128,128},  	// 16384
		{145,118},  	// 17110
		{167,107},  	// 17869
		{212,88},  	// 18656
		{191,102},  	// 19482
		{171,119},  	// 20349
		{166,128},  	// 21248
		{172,129},  	// 22188
		{181,128},  	// 23168
		{222,109},  	// 24198
		{190,133},  	// 25270
		{167,158},  	// 26386
		{167,165},  	// 27555
		{207,139},  	// 28773
		{199,151},  	// 30049
		{221,142},  	// 31382
		{217,151},  	// 32767
		{236,145},  	// 34220
		{214,167},  	// 35738
		{212,176},  	// 37312
		{204,191},  	// 38964
		{238,171},  	// 40698
		{250,170},  	// 42500
		{223,199},  	// 44377
		{225,206},  	// 46350
		{223,217},  	// 48391
		{243,208},  	// 50544
		{241,219},  	// 52779
		{246,224},  	// 55104
		{247,233},  	// 57551
		{245,245},  	// 60025
		{251,250},  	// 62750
		{255,255}  	// 65025
};
#endif//__GENERATED_PWM_LUT_LOG_COMP_8__
