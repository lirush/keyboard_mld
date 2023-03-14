/*
Copyright 2012,2013 Jun Wako <wakojun@gmail.com>

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

#ifndef _ACTION_H
#define _ACTION_H

#include "stdint_ch.h"
#include <stdbool.h>
#include "amekeyb.h"
#include "keycode.h"
#include "action_code.h"
//#include "action_macro.h"
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Disable macro and function features when LTO is enabled, since they break */
#ifdef LTO_ENABLE
#    ifndef NO_ACTION_MACRO
#        define NO_ACTION_MACRO
#    endif
#    ifndef NO_ACTION_FUNCTION
#        define NO_ACTION_FUNCTION
#    endif
#endif

/* tapping count and state */
typedef struct {
    bool    interrupted : 1;
    bool    reserved2 : 1;
    bool    reserved1 : 1;
    bool    reserved0 : 1;
    uint8_t count : 4;
} tap_t;

/* Key event container for recording */
typedef struct {
    keyevent_t event;
#ifndef NO_ACTION_TAPPING
    tap_t tap;
#endif
} keyrecord_t;

/* Execute action per keyevent */
void action_exec(keyevent_t event);

/* action for key */
action_t action_for_key(uint8_t layer, keypos_t key);

/* Utilities for actions.  */
#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
extern bool disable_action_cache;
#endif

/* Code for handling one-handed key modifiers. */
#ifdef SWAP_HANDS_ENABLE
extern bool           swap_hands;
extern const keypos_t hand_swap_config[MATRIX_ROWS][MATRIX_COLS];
#    if (MATRIX_COLS <= 8)
typedef uint8_t swap_state_row_t;
#    elif (MATRIX_COLS <= 16)
typedef uint16_t swap_state_row_t;
#    elif (MATRIX_COLS <= 32)
typedef uint32_t swap_state_row_t;
#    else
#        error "MATRIX_COLS: invalid value"
#    endif

void process_hand_swap(keyevent_t *record);
#endif

void register_weak_mods(uint8_t mods);
void unregister_weak_mods(uint8_t mods);

void register_mods(uint8_t mods);
void unregister_mods(uint8_t mods);
void process_record_handler(keyrecord_t *record);
void register_code(uint8_t code);
void unregister_code(uint8_t code);

void clear_keyboard(void);
void clear_keyboard_but_mods_and_keys(void);

#ifdef __cplusplus
}
#endif

#endif	//_ACTION_H
