#ifndef _USB_DEVICE_H
#define _USB_DEVICE_H

#include "stdint_ch.h"

#include "type.h"

#define KEYBOARD_REPORT_SIZE 8

#define KEYBOARD_REPORT_KEYS 6

/*
 * keyboard report is 8-byte array retains state of 8 modifiers and 6 keys.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |mods    |reserved|keys[0] |keys[1] |keys[2] |keys[3] |keys[4] |keys[5]
 *
 * It is exended to 16 bytes to retain 120keys+8mods when NKRO mode.
 *
 * byte |0       |1       |2       |3       |4       |5       |6       |7        ... |15
 * -----+--------+--------+--------+--------+--------+--------+--------+--------     +--------
 * desc |mods    |bits[0] |bits[1] |bits[2] |bits[3] |bits[4] |bits[5] |bits[6]  ... |bit[14]
 *
 * mods retains state of 8 modifiers.
 *
 *  bit |0       |1       |2       |3       |4       |5       |6       |7
 * -----+--------+--------+--------+--------+--------+--------+--------+--------
 * desc |Lcontrol|Lshift  |Lalt    |Lgui    |Rcontrol|Rshift  |Ralt    |Rgui
 *
 */
typedef union {
    uint8_t raw[KEYBOARD_REPORT_SIZE];
    struct {
#ifdef KEYBOARD_SHARED_EP
        uint8_t report_id;
#endif
        uint8_t mods;
        uint8_t reserved;
        uint8_t keys[KEYBOARD_REPORT_KEYS];
    };
#ifdef NKRO_ENABLE
    struct nkro_report {
#    ifdef NKRO_SHARED_EP
        uint8_t report_id;
#    endif
        uint8_t mods;
        uint8_t bits[KEYBOARD_REPORT_BITS];
    } nkro;
#endif
} __attribute__((packed)) report_keyboard_t;

uint8_t has_anykey(report_keyboard_t* keyboard_report);

bool is_key_pressed(report_keyboard_t* keyboard_report, uint8_t key);

void add_key_to_report(report_keyboard_t* keyboard_report, uint8_t key);

void del_key_from_report(report_keyboard_t* keyboard_report, uint8_t key);

void clear_keys_from_report(report_keyboard_t* keyboard_report);

#endif	//_USB_DEVICE_H


