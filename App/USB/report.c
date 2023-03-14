#include "report.h"
#include "keycode_config.h"

#include <string.h>

struct keyboardHID_t {
//      uint8_t id;
      uint8_t modifiers;
			uint8_t rezerv;
      uint8_t key1;
      uint8_t key2;
      uint8_t key3;
			uint8_t key4;
			uint8_t key5;
			uint8_t key6;
};
struct keyboardHID_t keyboardHID;

/** \brief has_anykey
 *
 * FIXME: Needs doc
 */
uint8_t has_anykey(report_keyboard_t* keyboard_report) {
    uint8_t  cnt = 0;
    uint8_t* p   = keyboard_report->keys;
    uint8_t  lp  = sizeof(keyboard_report->keys);
    while (lp--) {
        if (*p++) cnt++;
    }
    return cnt;
}

/** \brief Checks if a key is pressed in the report
 *
 * Returns true if the keyboard_report reports that the key is pressed, otherwise false
 * Note: The function doesn't support modifers currently, and it returns false for KC_NO
 */
bool is_key_pressed(report_keyboard_t* keyboard_report, uint8_t key) {
    if (key == KC_NO) {
        return 0;										//false
    }
    for (int i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == key) {
            return 1;							//true
        }
    }
    return 0;											//false
}

void add_key_byte(report_keyboard_t* keyboard_report, uint8_t code) {
    int8_t i     = 0;
    int8_t empty = -1;
    for (; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            break;
        }
        if (empty == -1 && keyboard_report->keys[i] == 0) {
            empty = i;
        }
    }
    if (i == KEYBOARD_REPORT_KEYS) {
        if (empty != -1) {
            keyboard_report->keys[empty] = code;
        }
    }
}

/** \brief del key byte
 *
 * FIXME: Needs doc
 */
void del_key_byte(report_keyboard_t* keyboard_report, uint8_t code) {
    for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
        if (keyboard_report->keys[i] == code) {
            keyboard_report->keys[i] = 0;
        }
    }
}

void add_key_to_report(report_keyboard_t* keyboard_report, uint8_t key) {
    add_key_byte(keyboard_report, key);
}

/** \brief del key from report
 *
 * FIXME: Needs doc
 */
void del_key_from_report(report_keyboard_t* keyboard_report, uint8_t key) {
    del_key_byte(keyboard_report, key);
}

/** \brief clear key from report
 *
 * FIXME: Needs doc
 */
void clear_keys_from_report(report_keyboard_t* keyboard_report) {
    // not clear mods
    memset(keyboard_report->keys, 0, sizeof(keyboard_report->keys));
}

