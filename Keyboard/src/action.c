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

#include "keycode.h"
#include "action_layer.h"
#include "action_util.h"
#include "action_tapping.h"
#include "wait.h"
#include "keymap.h"

#include "incudes.h"
#include "report.h"

#ifndef TAP_CODE_DELAY
#    define TAP_CODE_DELAY 0
#endif
#ifndef TAP_HOLD_CAPS_DELAY
#    define TAP_HOLD_CAPS_DELAY 80
#endif

int tp_buttons;

//#define LOCKING_SUPPORT_ENABLE

void process_action(keyrecord_t *record, action_t action);

#if !defined(NO_ACTION_LAYER) && !defined(STRICT_LAYER_RELEASE)
bool disable_action_cache = false;

//void process_record_nocache(keyrecord_t *record) {
//    disable_action_cache = true;
//    process_record(record);
//    disable_action_cache = false;
//}
#else
void process_record_nocache(keyrecord_t *record) { process_record_handler(record); }
#endif

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
void register_code(uint8_t code) {
    if (code == KC_NO) {
        return;
    }
#ifdef LOCKING_SUPPORT_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#    ifdef LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is on
//        if (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK)) return;
			
#    endif
        add_key(KC_CAPSLOCK);
        send_keyboard_report();
        wait_ms(100);
        del_key(KC_CAPSLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_NUM == code) {
#    ifdef LOCKING_RESYNC_ENABLE
//        if (host_keyboard_leds() & (1 << USB_LED_NUM_LOCK)) return;
#    endif
        add_key(KC_NUMLOCK);
        send_keyboard_report();
        wait_ms(100);
        del_key(KC_NUMLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_SCROLL == code) {
#    ifdef LOCKING_RESYNC_ENABLE
//        if (host_keyboard_leds() & (1 << USB_LED_SCROLL_LOCK)) return;
#    endif
        add_key(KC_SCROLLLOCK);
        send_keyboard_report();
        wait_ms(100);
        del_key(KC_SCROLLLOCK);
        send_keyboard_report();
    }
#endif

    else if
        IS_KEY(code) {
            // TODO: should push command_proc out of this block?
            //if (command_proc(code)) return;
						if (false) return;
            {
                // Force a new key press if the key is already pressed
                // without this, keys with the same keycode, but different
                // modifiers will be reported incorrectly, see issue #1708
                if (is_key_pressed(keyboard_report, code)) {
                    del_key(code);
                    send_keyboard_report();
                }
                add_key(code);
                send_keyboard_report();
            }
        }
    else if
        IS_MOD(code) {
            add_mods(MOD_BIT(code));
            send_keyboard_report();
        }
#ifdef EXTRAKEY_ENABLE
    else if
        IS_SYSTEM(code) { host_system_send(KEYCODE2SYSTEM(code)); }
    else if
        IS_CONSUMER(code) { host_consumer_send(KEYCODE2CONSUMER(code)); }
#endif
}

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
void unregister_code(uint8_t code) {
    if (code == KC_NO) {
        return;
    }
#ifdef LOCKING_SUPPORT_ENABLE
    else if (KC_LOCKING_CAPS == code) {
#    ifdef LOCKING_RESYNC_ENABLE
        // Resync: ignore if caps lock already is off
//        if (!(host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK))) return;
			
#    endif
        add_key(KC_CAPSLOCK);
        send_keyboard_report();
        del_key(KC_CAPSLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_NUM == code) {
#    ifdef LOCKING_RESYNC_ENABLE
//        if (!(host_keyboard_leds() & (1 << USB_LED_NUM_LOCK))) return;
#    endif
        add_key(KC_NUMLOCK);
        send_keyboard_report();
        del_key(KC_NUMLOCK);
        send_keyboard_report();
    }

    else if (KC_LOCKING_SCROLL == code) {
#    ifdef LOCKING_RESYNC_ENABLE
#    endif
        add_key(KC_SCROLLLOCK);
        send_keyboard_report();
        del_key(KC_SCROLLLOCK);
        send_keyboard_report();
    }
#endif

    else if
        IS_KEY(code) {
            del_key(code);
            send_keyboard_report();
        }
    else if
        IS_MOD(code) {
            del_mods(MOD_BIT(code));
            send_keyboard_report();
        }
}

/** \brief Adds the given physically pressed modifiers and sends a keyboard report immediately.
 *
 * \param mods A bitfield of modifiers to register.
 */
void register_mods(uint8_t mods) {
    if (mods) {
        add_mods(mods);
        send_keyboard_report();
    }
}

/** \brief Removes the given physically pressed modifiers and sends a keyboard report immediately.
 *
 * \param mods A bitfield of modifiers to unregister.
 */
void unregister_mods(uint8_t mods) {
    if (mods) {
        del_mods(mods);
        send_keyboard_report();
    }
}

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
void clear_keyboard_but_mods(void) {
    clear_keys();
    clear_keyboard_but_mods_and_keys();
}

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
void clear_keyboard(void) {
    clear_mods();
    clear_keyboard_but_mods();
}

/** \brief Utilities for actions. (FIXME: Needs better description)
 *
 * FIXME: Needs documentation.
 */
void clear_keyboard_but_mods_and_keys() {
    clear_weak_mods();
    clear_macro_mods();
    send_keyboard_report();
#ifdef MOUSEKEY_ENABLE
    mousekey_clear();
    mousekey_send();
#endif
#ifdef EXTRAKEY_ENABLE
    host_system_send(0);
    host_consumer_send(0);
#endif
}

/** \brief Called to execute an action.
 *
 * FIXME: Needs documentation.
 */
uint16_t keycode =0; 
void action_exec(keyevent_t event) {

 keyrecord_t record = {.event = event};

 process_record_handler(&record);

}

void process_record_handler(keyrecord_t *record) {
	
    action_t action = store_or_get_action(record->event.pressed, record->event.key);

    process_action(record, action);
}

/** \brief Take an action and processes it.
 *
 * FIXME: Needs documentation.
 */
void process_action(keyrecord_t *record, action_t action) {
    keyevent_t event = record->event;
#ifndef NO_ACTION_TAPPING
    uint8_t tap_count = record->tap.count;
#endif

    if (event.pressed) {
        // clear the potential weak mods left by previously pressed keys
        clear_weak_mods();
    }

    switch (action.kind.id) {
        /* Key and Mods */
        case ACT_LMODS:
        case ACT_RMODS: {
            uint8_t mods = (action.kind.id == ACT_LMODS) ? action.key.mods : action.key.mods << 4;
            if (event.pressed) {
                if (mods) {
                    if (IS_MOD(action.key.code) || action.key.code == KC_NO) {
                        // e.g. LSFT(KC_LGUI): we don't want the LSFT to be weak as it would make it useless.
                        // This also makes LSFT(KC_LGUI) behave exactly the same as LGUI(KC_LSFT).
                        // Same applies for some keys like KC_MEH which are declared as MEH(KC_NO).
                        add_mods(mods);
                    } else {
                        add_weak_mods(mods);
                    }
                    send_keyboard_report();
                }
                register_code(action.key.code);
            } else {
                unregister_code(action.key.code);
                if (mods) {
                    if (IS_MOD(action.key.code) || action.key.code == KC_NO) {
                        del_mods(mods);
                    } else {
                        del_weak_mods(mods);
                    }
                    send_keyboard_report();
                }
            }
        } break;
#ifndef NO_ACTION_LAYER
        case ACT_LAYER:
            if (action.layer_bitop.on == 0) {
                /* Default Layer Bitwise Operation */
                if (!event.pressed) {
                    uint8_t       shift = action.layer_bitop.part * 4;
                    layer_state_t bits  = ((layer_state_t)action.layer_bitop.bits) << shift;
                    layer_state_t mask  = (action.layer_bitop.xbit) ? ~(((layer_state_t)0xf) << shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND:
                            default_layer_and(bits | mask);
                            break;
                        case OP_BIT_OR:
                            default_layer_or(bits | mask);
                            break;
                        case OP_BIT_XOR:
                            default_layer_xor(bits | mask);
                            break;
                        case OP_BIT_SET:
                            default_layer_set(bits | mask);
                            break;
                    }
                }
            } else {
                /* Layer Bitwise Operation */
                if (event.pressed ? (action.layer_bitop.on & ON_PRESS) : (action.layer_bitop.on & ON_RELEASE)) {
                    uint8_t       shift = action.layer_bitop.part * 4;
                    layer_state_t bits  = ((layer_state_t)action.layer_bitop.bits) << shift;
                    layer_state_t mask  = (action.layer_bitop.xbit) ? ~(((layer_state_t)0xf) << shift) : 0;
                    switch (action.layer_bitop.op) {
                        case OP_BIT_AND:
                            layer_and(bits | mask);
                            break;
                        case OP_BIT_OR:
                            layer_or(bits | mask);
                            break;
                        case OP_BIT_XOR:
                            layer_xor(bits | mask);
                            break;
                        case OP_BIT_SET:
                            layer_state_set(bits | mask);
                            break;
                    }
                }
            }
            break;
        case ACT_LAYER_MODS:
            if (event.pressed) {
                layer_on(action.layer_mods.layer);
                register_mods(action.layer_mods.mods);
            } else {
                unregister_mods(action.layer_mods.mods);
                layer_off(action.layer_mods.layer);
            }
            break;
#    ifndef NO_ACTION_TAPPING
        case ACT_LAYER_TAP:
        case ACT_LAYER_TAP_EXT:
            switch (action.layer_tap.code) {
                case OP_TAP_TOGGLE:
                    /* tap toggle */
                    if (event.pressed) {
                        if (tap_count < TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count <= TAPPING_TOGGLE) {
                            layer_invert(action.layer_tap.val);
                        }
                    }
                    break;
                case OP_ON_OFF:
                    event.pressed ? layer_on(action.layer_tap.val) : layer_off(action.layer_tap.val);
                    break;
                case OP_OFF_ON:
                    event.pressed ? layer_off(action.layer_tap.val) : layer_on(action.layer_tap.val);
                    break;
                case OP_SET_CLEAR:
                    event.pressed ? layer_move(action.layer_tap.val) : layer_clear();
                    break;
#        ifndef NO_ACTION_ONESHOT
                case OP_ONESHOT:
                    // Oneshot modifier
#            if defined(ONESHOT_TAP_TOGGLE) && ONESHOT_TAP_TOGGLE > 1
                    do_release_oneshot = false;
                    if (event.pressed) {
                        del_mods(get_oneshot_locked_mods());
                        if (get_oneshot_layer_state() == ONESHOT_TOGGLED) {
                            reset_oneshot_layer();
                            layer_off(action.layer_tap.val);
                            break;
                        } else if (tap_count < ONESHOT_TAP_TOGGLE) {
                            layer_on(action.layer_tap.val);
                            set_oneshot_layer(action.layer_tap.val, ONESHOT_START);
                        }
                    } else {
                        add_mods(get_oneshot_locked_mods());
                        if (tap_count >= ONESHOT_TAP_TOGGLE) {
                            reset_oneshot_layer();
                            clear_oneshot_locked_mods();
                            set_oneshot_layer(action.layer_tap.val, ONESHOT_TOGGLED);
                        } else {
                            clear_oneshot_layer_state(ONESHOT_PRESSED);
                        }
                    }
#            else
                    if (event.pressed) {
                        layer_on(action.layer_tap.val);
                        set_oneshot_layer(action.layer_tap.val, ONESHOT_START);
                    } else {
                        clear_oneshot_layer_state(ONESHOT_PRESSED);
                        if (tap_count > 1) {
                            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                        }
                    }
#            endif
                    break;
#        endif
                default:
                    /* tap key */
                    if (event.pressed) {
                        if (tap_count > 0) {
//                            dprint("KEYMAP_TAP_KEY: Tap: register_code\n");
                            register_code(action.layer_tap.code);
                        } else {
//                            dprint("KEYMAP_TAP_KEY: No tap: On on press\n");
                            layer_on(action.layer_tap.val);
                        }
                    } else {
                        if (tap_count > 0) {
//                            dprint("KEYMAP_TAP_KEY: Tap: unregister_code\n");
                            if (action.layer_tap.code == KC_CAPS) {
                                wait_ms(TAP_HOLD_CAPS_DELAY);
                            } else {
                                wait_ms(TAP_CODE_DELAY);
                            }
                            unregister_code(action.layer_tap.code);
                        } else {
//                            dprint("KEYMAP_TAP_KEY: No tap: Off on release\n");
                            layer_off(action.layer_tap.val);
                        }
                    }
                    break;
            }
            break;
#    endif
#endif
            /* Extentions */
        default:
            break;
    }
}
