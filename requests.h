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

//Request ids
#define LAMP_REQ_SET_LED	1
#define LAMP_REQ_PUSH_LED	4
//For powering on and powering off
#define LAMP_REQ_POWER		2
#define LAMP_REQ_STATE		3

typedef struct {
	unsigned short r, g, b;
} color;

typedef struct {
	unsigned char poweron;
	color c;
} statestruct;

