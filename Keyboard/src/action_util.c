/*
Copyright 2013 Jun Wako <wakojun@gmail.com>

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
#include "report.h"
#include "action_util.h"
#include "action_layer.h"
#include "keycode_config.h"
#include "vusb.h"

extern keymap_config_t keymap_config;

static uint8_t real_mods  = 0;
static uint8_t weak_mods  = 0;
static uint8_t macro_mods = 0;

// TODO: pointer variable is not needed
report_keyboard_t *keyboard_report = &(report_keyboard_t){};

extern inline void add_key(uint8_t key);
extern inline void del_key(uint8_t key);
extern inline void clear_keys(void);

#ifndef NO_ACTION_ONESHOT
static uint8_t oneshot_mods        = 0;
static uint8_t oneshot_locked_mods = 0;
uint8_t        get_oneshot_locked_mods(void) { return oneshot_locked_mods; }
void           set_oneshot_locked_mods(uint8_t mods) {
    if (mods != oneshot_locked_mods) {
        oneshot_locked_mods = mods;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
void clear_oneshot_locked_mods(void) {
    if (oneshot_locked_mods) {
        oneshot_locked_mods = 0;
        oneshot_locked_mods_changed_kb(oneshot_locked_mods);
    }
}
#endif

/* oneshot layer */
#ifndef NO_ACTION_ONESHOT
/** \brief oneshot_layer_data bits
 * LLLL LSSS
 * where:
 *   L => are layer bits
 *   S => oneshot state bits
 */
static int8_t oneshot_layer_data = 0;

inline uint8_t get_oneshot_layer(void) { return oneshot_layer_data >> 3; }
inline uint8_t get_oneshot_layer_state(void) { return oneshot_layer_data & 0b111; }


/** \brief Reset oneshot layer
 *
 * FIXME: needs doc
 */
void reset_oneshot_layer(void) {
    oneshot_layer_data = 0;
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
    oneshot_layer_time = 0;
#    endif
    oneshot_layer_changed_kb(get_oneshot_layer());
}

#endif

/** \brief Send keyboard report
 *
 * FIXME: needs doc
 */
void send_keyboard_report(void) {
    keyboard_report->mods = real_mods;
    keyboard_report->mods |= weak_mods;
    keyboard_report->mods |= macro_mods;
#ifndef NO_ACTION_ONESHOT
    if (oneshot_mods) {
#    if (defined(ONESHOT_TIMEOUT) && (ONESHOT_TIMEOUT > 0))
        if (has_oneshot_mods_timed_out()) {
            dprintf("Oneshot: timeout\n");
            clear_oneshot_mods();
        }
#    endif
        keyboard_report->mods |= oneshot_mods;
        if (has_anykey(keyboard_report)) {
            clear_oneshot_mods();
        }
    }

#endif
    host_keyboard_send(keyboard_report);
}

/** \brief Get mods
 *
 * FIXME: needs doc
 */
uint8_t get_mods(void) { return real_mods; }
/** \brief add mods
 *
 * FIXME: needs doc
 */
void add_mods(uint8_t mods) { real_mods |= mods; }
/** \brief del mods
 *
 * FIXME: needs doc
 */
void del_mods(uint8_t mods) { real_mods &= ~mods; }
/** \brief set mods
 *
 * FIXME: needs doc
 */
void set_mods(uint8_t mods) { real_mods = mods; }
/** \brief clear mods
 *
 * FIXME: needs doc
 */
void clear_mods(void) { real_mods = 0; }

/** \brief get weak mods
 *
 * FIXME: needs doc
 */
uint8_t get_weak_mods(void) { return weak_mods; }
/** \brief add weak mods
 *
 * FIXME: needs doc
 */
void add_weak_mods(uint8_t mods) { weak_mods |= mods; }
/** \brief del weak mods
 *
 * FIXME: needs doc
 */
void del_weak_mods(uint8_t mods) { weak_mods &= ~mods; }
/** \brief set weak mods
 *
 * FIXME: needs doc
 */
void set_weak_mods(uint8_t mods) { weak_mods = mods; }
/** \brief clear weak mods
 *
 * FIXME: needs doc
 */
void clear_weak_mods(void) { weak_mods = 0; }

/* macro modifier */
/** \brief get macro mods
 *
 * FIXME: needs doc
 */
uint8_t get_macro_mods(void) { return macro_mods; }
/** \brief add macro mods
 *
 * FIXME: needs doc
 */
void add_macro_mods(uint8_t mods) { macro_mods |= mods; }
/** \brief del macro mods
 *
 * FIXME: needs doc
 */
void del_macro_mods(uint8_t mods) { macro_mods &= ~mods; }
/** \brief set macro mods
 *
 * FIXME: needs doc
 */
void set_macro_mods(uint8_t mods) { macro_mods = mods; }
/** \brief clear macro mods
 *
 * FIXME: needs doc
 */
void clear_macro_mods(void) { macro_mods = 0; }

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_user(uint8_t mods) {}

/** \brief Called when the locked one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_locked_mods_changed_kb(uint8_t mods) { oneshot_locked_mods_changed_user(mods); }

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_user(uint8_t mods) {}

/** \brief Called when the one shot modifiers have been changed.
 *
 * \param mods Contains the active modifiers active after the change.
 */
__attribute__((weak)) void oneshot_mods_changed_kb(uint8_t mods) { oneshot_mods_changed_user(mods); }

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_user(uint8_t layer) {}

/** \brief Called when the one shot layers have been changed.
 *
 * \param layer Contains the layer that is toggled on, or zero when toggled off.
 */
__attribute__((weak)) void oneshot_layer_changed_kb(uint8_t layer) { oneshot_layer_changed_user(layer); }
