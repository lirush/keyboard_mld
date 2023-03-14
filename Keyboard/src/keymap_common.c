/*
Copyright 2012-2017 Jun Wako <wakojun@gmail.com>

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

#include "keymap.h"
#include "action.h"
//#include "keycode.h"
#include "_keycodes.h"

#include <inttypes.h>

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key) {
    // 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    // keycode remapping
    keycode = keycode_config(keycode);

    action_t action = {};
    uint8_t  action_layer, when, mod;

    (void)action_layer;
    (void)when;
    (void)mod;

    switch (keycode) {
        case KC_A ... KC_EXSEL:
        case KC_LCTRL ... KC_RGUI:
            action.code = ACTION_KEY(keycode);
            break;
        case KC_TRNS:
            action.code = ACTION_TRANSPARENT;
            break;
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
            break;
        case QK_TO ... QK_TO_MAX:
            // Layer set "GOTO"
            when         = (keycode >> 0x4) & 0x3;
            action_layer = keycode & 0xF;
            action.code  = ACTION_LAYER_SET(action_layer, when);
            break;
        case QK_MOMENTARY ... QK_MOMENTARY_MAX:
            // Momentary action_layer
            action_layer = keycode & 0xFF;
            action.code  = ACTION_LAYER_MOMENTARY(action_layer);
            break;
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            // Set default action_layer
            action_layer = keycode & 0xFF;
            action.code  = ACTION_DEFAULT_LAYER_SET(action_layer);
            break;
        case QK_TOGGLE_LAYER ... QK_TOGGLE_LAYER_MAX:
            // Set toggle
            action_layer = keycode & 0xFF;
            action.code  = ACTION_LAYER_TOGGLE(action_layer);
            break;
#endif
#ifndef NO_ACTION_LAYER
        case QK_LAYER_TAP_TOGGLE ... QK_LAYER_TAP_TOGGLE_MAX:
            action.code = ACTION_LAYER_TAP_TOGGLE(keycode & 0xFF);
            break;
        case QK_LAYER_MOD ... QK_LAYER_MOD_MAX:
            mod          = mod_config(keycode & 0xF);
            action_layer = (keycode >> 4) & 0xF;
            action.code  = ACTION_LAYER_MODS(action_layer, mod);
            break;
#endif
        default:
            action.code = ACTION_NO;
            break;
    }
    return action;
}

// translates key to keycode
__attribute__((weak)) uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    // Read entire word (16bits)
			return keymaps[layer][key.row][key.col];
}
