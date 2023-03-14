/*
Copyright 2017 Alex Ong<the.onga@gmail.com>
Copyright 2020 Andrei Purdea<andrei@purdea.ro>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
Basic symmetric per-key algorithm. Uses an 8-bit counter per key.
When no state changes have occured for DEBOUNCE milliseconds, we push the state.
*/
#include "debounce.h"
#include <stdlib.h>
#include "config.h"
#include "timer_a.h"

#ifndef DEBOUNCE
#    define DEBOUNCE 5
#endif

#define debounce_counter_t uint8_t
static debounce_counter_t *debounce_counters;

#define DEBOUNCE_ELAPSED 251
#define MAX_DEBOUNCE (DEBOUNCE_ELAPSED - 1)

// we use num_rows rather than MATRIX_ROWS to support split keyboards
void debounce_init(unsigned char num_rows) {
    debounce_counters = (debounce_counter_t *)malloc(num_rows * MATRIX_COLS * sizeof(debounce_counter_t));
    int i             = 0;
    for (uint8_t r = 0; r < num_rows; r++) {
        for (uint8_t c = 0; c < MATRIX_COLS; c++) {
            debounce_counters[i++] = DEBOUNCE_ELAPSED;
        }
    }
}

static bool debouncing = false;

#if DEBOUNCE > 0
static uint16_t debouncing_time;
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    if (changed) {
        debouncing      = true;
        debouncing_time = timer_read();
    }

    if (debouncing && timer_elapsed(debouncing_time) > DEBOUNCE) {
        for (int i = 0; i < num_rows; i++) {
            cooked[i] = raw[i];
        }
        debouncing = false;
    }
}
#else  // no debouncing.
void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed) {
    for (int i = 0; i < num_rows; i++) {
        cooked[i] = raw[i];
    }
}
#endif
