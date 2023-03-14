/* Copyright 2016-2017 Jack Humbert
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

#ifndef __KEYCODES_H
#define __KEYCODES_H

// #if defined(SEQUENCER_ENABLE)
// #    include "sequencer.h"
// #endif

// #ifndef MIDI_ENABLE_STRICT
// #    define MIDI_ENABLE_STRICT 0
// #endif

// #if !MIDI_ENABLE_STRICT || (defined(MIDI_ENABLE) && defined(MIDI_ADVANCED))
// #    ifndef MIDI_TONE_KEYCODE_OCTAVES
// #        define MIDI_TONE_KEYCODE_OCTAVES 3
// #    endif
// #endif

// // Fillers to make layering more clear
// #define _______ KC_TRNS
// #define XXXXXXX KC_NO

 enum quantum_keycodes {
     QK_LAYER_TAP            = 0x4000,
     QK_LAYER_TAP_MAX        = 0x4FFF,
     QK_TO                   = 0x5000,
     QK_TO_MAX               = 0x50FF,
     QK_MOMENTARY            = 0x5100,
     QK_MOMENTARY_MAX        = 0x51FF,
     QK_DEF_LAYER            = 0x5200,
     QK_DEF_LAYER_MAX        = 0x52FF,
     QK_TOGGLE_LAYER         = 0x5300,
     QK_TOGGLE_LAYER_MAX     = 0x53FF,
     QK_LAYER_TAP_TOGGLE     = 0x5800,
     QK_LAYER_TAP_TOGGLE_MAX = 0x58FF,
     QK_LAYER_MOD            = 0x5900,
     QK_LAYER_MOD_MAX        = 0x59FF,

 };

// L-ayer, T-ap - 256 keycode max, 16 layer max
#define LT(layer, kc) (QK_LAYER_TAP | (((layer)&0xF) << 8) | ((kc)&0xFF))
 
 // Toggle to layer - 256 layer max
#ifdef NO_ACTION_LAYER
#define FUN_APP				KC_APP
#else
#define FUN_APP				(QK_TOGGLE_LAYER | ((_FL)&0xFF))
#endif
#define TG(layer) (QK_TOGGLE_LAYER | ((layer)&0xFF))

#endif	//_QUANTUM_KEYCODES_H
