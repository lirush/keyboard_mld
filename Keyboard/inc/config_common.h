/* Copyright 2015-2018 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _CONFIG_COMMON_H
#define _CONFIG_COMMON_H

#include "MDR32F9Qx_port.h"

#include "pal_lld.h"

/* diode directions */
#define COL2ROW 0
#define ROW2COL 1

//// useful for direct pin mapping
//#define NO_PIN (pin_t)(~0)

#        define A0 PAL_LINE(MDR_PORTA, 0)
#        define A1 PAL_LINE(MDR_PORTA, 1)
#        define A2 PAL_LINE(MDR_PORTA, 2)
#        define A3 PAL_LINE(MDR_PORTA, 3)
#        define A4 PAL_LINE(MDR_PORTA, 4)
#        define A5 PAL_LINE(MDR_PORTA, 5)
#        define A6 PAL_LINE(MDR_PORTA, 6)
#        define A7 PAL_LINE(MDR_PORTA, 7)
#        define B0 PAL_LINE(MDR_PORTB, 0)
#        define B1 PAL_LINE(MDR_PORTB, 1)
#        define B2 PAL_LINE(MDR_PORTB, 2)
#        define B3 PAL_LINE(MDR_PORTB, 3)
#        define B4 PAL_LINE(MDR_PORTB, 4)
#        define B5 PAL_LINE(MDR_PORTB, 5)
#        define B6 PAL_LINE(MDR_PORTB, 6)
#        define B7 PAL_LINE(MDR_PORTB, 7)
#        define B8 PAL_LINE(MDR_PORTB, 8)
#        define B9 PAL_LINE(MDR_PORTB, 9)
#        define B10 PAL_LINE(MDR_PORTB, 10)
#        define F0 PAL_LINE(MDR_PORTF, 0)
#        define F1 PAL_LINE(MDR_PORTF, 1)
#        define F2 PAL_LINE(MDR_PORTF, 2)

#        define E0 PAL_LINE(MDR_PORTE, 0)
#        define E1 PAL_LINE(MDR_PORTE, 1)
//#        define D7 PAL_LINE(MDR_PORTD, 7)

#endif //_CONFIG_COMMON_H
