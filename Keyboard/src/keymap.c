#include "keymap.h"
#include "incudes.h"
#include "_keycodes.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
#define _BL 0
#define _FL 1
#define _CL 2

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = LAYOUT(																																																																		\
  KC_ESC,			KC_F1,  	KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  	KC_F7,  	KC_F8,  			KC_F9,  	KC_F10,		KC_PSCR,	KC_PAUS,	KC_PSLS,	KC_PMNS,	\
  KC_GRAVE,		KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_8,			KC_9,			KC_0,					KC_MINUS,	KC_F11,		KC_SLCK,	KC_PGUP,	KC_P8,		KC_PAST,	\
  KC_TAB,			KC_Q,			KC_W,		KC_E,		KC_R,		KC_6,		KC_I,			KC_O,			KC_P,					KC_EQUAL,	KC_F12,		KC_HOME,	KC_PGDN,	KC_P5,		KC_P9,		\
  KC_CAPS,		KC_A,   	KC_S,   KC_D,		KC_T,		KC_7,		KC_K,   	KC_L,			KC_LBRC,			KC_RBRC,	KC_BSPC,	KC_END,		KC_NLCK,	KC_P2,		KC_P6,		\
  KC_LSFT,    KC_Z, 		KC_X,		KC_F,		KC_Y,   KC_U,		KC_COMM,	KC_SCLN,	KC_QUOT,			KC_BSLS,	KC_INS,		KC_UP,		KC_P7,		KC_P0,		KC_PPLS,	\
  KC_LCTL,		KC_LALT,	KC_C,		KC_G,   KC_H,   KC_J,		KC_DOT,		KC_SLASH,	KC_RSFT,			KC_ENT,		KC_DEL,		KC_DOWN,	KC_P4,		KC_PDOT,	KC_PENT,	\
  KC_LWIN,		KC_SPC,		KC_V,   KC_B,   KC_N,   KC_M,		KC_RALT,	KC_RWIN,	FUN_APP,	KC_RCTL,	KC_LEFT,	KC_RGHT,	KC_P1,		KC_P3,		KC_NO),		\
[_FL] = LAYOUT(																																																																
  KC_NO,	KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  				KC_NO,  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,					KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_NO,	KC_NO,	KC_F8,	KC_F9,					KC_F10,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_NO,  KC_NO,  KC_NO,  KC_F5,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  				KC_NO,  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_NO,  KC_NO,  KC_NO,  KC_F6,  KC_F7,  KC_NO,  KC_NO,  KC_NO,  				KC_NO,  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  				KC_NO,  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	\
  KC_NO,	KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  FUN_APP,  	KC_NO,  KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO)	\
};
