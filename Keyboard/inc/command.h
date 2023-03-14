#ifndef _COMMAND_H
#define _COMMAND_H

/* FIXME: Add doxygen comments for the behavioral defines in here. */

/* TODO: Refactoring */
typedef enum { ONESHOT, CONSOLE, MOUSEKEY } command_state_t;
extern command_state_t command_state;

//#ifdef COMMAND_ENABLE
//uint8_t numkey2num(uint8_t code);
//bool    command_proc(uint8_t code);
//#else
//#    define command_proc(code) false
//#endif

#ifndef MAGIC_KEY_HELP
#    define MAGIC_KEY_HELP H
#endif

#ifndef MAGIC_KEY_HELP_ALT
#    define MAGIC_KEY_HELP_ALT SLASH
#endif

#ifndef MAGIC_KEY_CONSOLE
#    define MAGIC_KEY_CONSOLE C
#endif

#ifndef MAGIC_KEY_BOOTLOADER
#    define MAGIC_KEY_BOOTLOADER B
#endif

#ifndef MAGIC_KEY_BOOTLOADER_ALT
#    define MAGIC_KEY_BOOTLOADER_ALT ESC
#endif

#ifndef MAGIC_KEY_DEBUG
#    define MAGIC_KEY_DEBUG D
#endif

#ifndef MAGIC_KEY_DEBUG_MATRIX
#    define MAGIC_KEY_DEBUG_MATRIX X
#endif

#ifndef MAGIC_KEY_DEBUG_KBD
#    define MAGIC_KEY_DEBUG_KBD K
#endif

#ifndef MAGIC_KEY_DEBUG_MOUSE
#    define MAGIC_KEY_DEBUG_MOUSE M
#endif

#ifndef MAGIC_KEY_VERSION
#    define MAGIC_KEY_VERSION V
#endif

#ifndef MAGIC_KEY_STATUS
#    define MAGIC_KEY_STATUS S
#endif

#ifndef MAGIC_KEY_LAYER0_ALT
#    define MAGIC_KEY_LAYER0_ALT GRAVE
#endif

#ifndef MAGIC_KEY_EEPROM
#    define MAGIC_KEY_EEPROM E
#endif

#ifndef MAGIC_KEY_EEPROM_CLEAR
#    define MAGIC_KEY_EEPROM_CLEAR BSPACE
#endif


#ifndef IS_COMMAND
#    define IS_COMMAND() (get_mods() == MOD_MASK_SHIFT)
#endif

#define XMAGIC_KC(key) KC_##key
#define MAGIC_KC(key) XMAGIC_KC(key)

#endif
