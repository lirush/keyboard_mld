/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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

#ifndef _ACTION_TPPING_H
#define _ACTION_TPPING_H

/* period of tapping(ms) */
#ifndef TAPPING_TERM
#    define TAPPING_TERM 200
#endif

/* tap count needed for toggling a feature */
#ifndef TAPPING_TOGGLE
#    define TAPPING_TOGGLE 5
#endif

//#define WAITING_BUFFER_SIZE 8

//#ifndef NO_ACTION_TAPPING
//uint16_t get_event_keycode(keyevent_t event, bool update_layer_cache);
//void     action_tapping_process(keyrecord_t record);

//uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record);
//bool     get_permissive_hold(uint16_t keycode, keyrecord_t *record);
//bool     get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record);
//bool     get_tapping_force_hold(uint16_t keycode, keyrecord_t *record);
//bool     get_retro_tapping(uint16_t keycode, keyrecord_t *record);
//#endif

#endif //_ACTION_TPPING_H
