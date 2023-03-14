#ifndef _KEYMAP_H
#define _KEYMAP_H

#include "stdint_ch.h"

#include "keycode.h"
#include "incudes.h"
#include "keycode_config.h"

// translates key to keycode
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key);

extern const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS];

#endif	//_KEYMAP_H
