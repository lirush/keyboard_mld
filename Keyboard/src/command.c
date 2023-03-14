#include "command.h"
#include <stdint.h>
#include <stdbool.h>
#include "action_util.h"
#include "action_layer.h"
#include "keycode.h"

static bool command_common(uint8_t code);
static void switch_default_layer(uint8_t layer);
static bool command_console(uint8_t code);
command_state_t command_state = ONESHOT;

/* TODO: Refactoring is needed. */
/* This allows to define extra commands. return false when not processed. */
bool command_extra(uint8_t code) __attribute__((weak));
bool command_extra(uint8_t code) {
    (void)code;
    return false;
}

bool command_console_extra(uint8_t code) __attribute__((weak));
bool command_console_extra(uint8_t code) {
    (void)code;
    return false;
}

bool command_proc(uint8_t code) {
    switch (command_state) {
        case ONESHOT:
            if (!IS_COMMAND()) return false;
            return (command_extra(code) || command_common(code));
            break;
        case CONSOLE:
            if (IS_COMMAND())
                return (command_extra(code) || command_common(code));
            else
                return (command_console_extra(code) || command_console(code));
            break;
#if defined(MOUSEKEY_ENABLE) && !defined(MK_3_SPEED)
        case MOUSEKEY:
            mousekey_console(code);
            break;
#endif
        default:
            command_state = ONESHOT;
            return false;
    }
    return true;
}

static bool command_common(uint8_t code) {
#ifdef KEYBOARD_LOCK_ENABLE
    static host_driver_t *host_driver = 0;
#endif

    switch (code) {
#ifdef SLEEP_LED_ENABLE

        // test breathing sleep LED
        case MAGIC_KC(MAGIC_KEY_SLEEP_LED):
            print("Sleep LED Test\n");
            sleep_led_toggle();
            led_set(host_keyboard_leds());
            break;
#endif

        // print stored eeprom config
        case MAGIC_KC(MAGIC_KEY_EEPROM):
//            print("eeconfig:\n");
//            print_eeconfig();
            break;

        // clear eeprom
        case MAGIC_KC(MAGIC_KEY_EEPROM_CLEAR):
//            print("Clearing EEPROM\n");
//            eeconfig_init();	
            break;

#ifdef KEYBOARD_LOCK_ENABLE

        // lock/unlock keyboard
        case MAGIC_KC(MAGIC_KEY_LOCK):
            if (host_get_driver()) {
                host_driver = host_get_driver();
                clear_keyboard();
                host_set_driver(0);
                print("Locked.\n");
            } else {
                host_set_driver(host_driver);
                print("Unlocked.\n");
            }
            break;
#endif

        // print help
        case MAGIC_KC(MAGIC_KEY_HELP):
        case MAGIC_KC(MAGIC_KEY_HELP_ALT):
//            command_common_help();
            break;

        // activate console
        case MAGIC_KC(MAGIC_KEY_CONSOLE):
//            debug_matrix   = false;
//            debug_keyboard = false;
//            debug_mouse    = false;
//            debug_enable   = false;
//            command_console_help();
//            print("C> ");
            command_state = CONSOLE;
            break;

        // jump to bootloader
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER):
        case MAGIC_KC(MAGIC_KEY_BOOTLOADER_ALT):
//            print("\n\nJumping to bootloader... ");
//            reset_keyboard();
            break;

        // debug toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG):
//            debug_enable = !debug_enable;
//            if (debug_enable) {
//                print("\ndebug: on\n");
//            } else {
//                print("\ndebug: off\n");
//                debug_matrix   = false;
//                debug_keyboard = false;
//                debug_mouse    = false;
//            }
            break;

        // debug matrix toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MATRIX):
//            debug_matrix = !debug_matrix;
//            if (debug_matrix) {
//                print("\nmatrix: on\n");
//                debug_enable = true;
//            } else {
//                print("\nmatrix: off\n");
//            }
            break;

        // debug keyboard toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_KBD):
//            debug_keyboard = !debug_keyboard;
//            if (debug_keyboard) {
//                print("\nkeyboard: on\n");
//                debug_enable = true;
//            } else {
//                print("\nkeyboard: off\n");
//            }
            break;

        // debug mouse toggle
        case MAGIC_KC(MAGIC_KEY_DEBUG_MOUSE):
//            debug_mouse = !debug_mouse;
//            if (debug_mouse) {
//                print("\nmouse: on\n");
//                debug_enable = true;
//            } else {
//                print("\nmouse: off\n");
//            }
            break;

        // print version
        case MAGIC_KC(MAGIC_KEY_VERSION):
//            print_version();
            break;

        // print status
        case MAGIC_KC(MAGIC_KEY_STATUS):
//            print_status();
            break;

#ifdef NKRO_ENABLE

        // NKRO toggle
        case MAGIC_KC(MAGIC_KEY_NKRO):
            clear_keyboard();  // clear to prevent stuck keys
            keymap_config.nkro = !keymap_config.nkro;
            if (keymap_config.nkro) {
                print("NKRO: on\n");
            } else {
                print("NKRO: off\n");
            }
            break;
#endif

            // switch layers

        case MAGIC_KC(MAGIC_KEY_LAYER0_ALT):
            switch_default_layer(0);
            break;

#if MAGIC_KEY_SWITCH_LAYER_WITH_CUSTOM

        case MAGIC_KC(MAGIC_KEY_LAYER0):
            switch_default_layer(0);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER1):
            switch_default_layer(1);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER2):
            switch_default_layer(2);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER3):
            switch_default_layer(3);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER4):
            switch_default_layer(4);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER5):
            switch_default_layer(5);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER6):
            switch_default_layer(6);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER7):
            switch_default_layer(7);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER8):
            switch_default_layer(8);
            break;

        case MAGIC_KC(MAGIC_KEY_LAYER9):
            switch_default_layer(9);
            break;
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_FKEYS

        case KC_F1 ... KC_F9:
            switch_default_layer((code - KC_F1) + 1);
            break;
        case KC_F10:
            switch_default_layer(0);
            break;
#endif

#if MAGIC_KEY_SWITCH_LAYER_WITH_NKEYS

        case KC_1 ... KC_9:
            switch_default_layer((code - KC_1) + 1);
            break;
        case KC_0:
            switch_default_layer(0);
            break;
#endif

        default:
//            print("?");
            return false;
    }
    return true;
}

static void switch_default_layer(uint8_t layer) {
//    xprintf("L%d\n", layer);
    default_layer_set(1UL << layer);
    clear_keyboard();
}

static bool command_console(uint8_t code) {
    switch (code) {
        case KC_H:
        case KC_SLASH: /* ? */
//            command_console_help();
            break;
        case KC_Q:
        case KC_ESC:
            command_state = ONESHOT;
            return false;
#if defined(MOUSEKEY_ENABLE) && !defined(MK_3_SPEED)
        case KC_M:
            mousekey_console_help();
            print("M> ");
            command_state = MOUSEKEY;
            return true;
#endif
        default:
//            print("?");
            return false;
    }
//    print("C> ");
    return true;
}

