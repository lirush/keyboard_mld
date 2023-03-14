#ifndef _AMEKEYB_H
#define _AMEKEYB_H

#include "stdint_ch.h"

#include "pal.h"
#include "pal_lld.h"

typedef ioline_t pin_t;

#define setPinInput(pin) palClearLineOutEn(pin, PAL_MODE_INPUT)
#define setPinInputHigh(pin) palSetLinePull(pin, PAL_MODE_INPUT_PULLUP)
#define setPinInputLow(pin) palSetLineMode(pin, PAL_MODE_INPUT_PULLDOWN)
#define setPinOutput(pin) palSetLineOutEn(pin, PAL_MODE_OUTPUT_PUSHPULL)
#define clearPinPullUp(pin) palClearLinePull(pin, PAL_MODE_INPUT_PULLUP)

#define setPinDigital(pin) palSetLineDigital(pin)
#define setPinPower(pin) palSetLinePower(pin)

#define writePinHigh(pin) palSetLine(pin)
#define writePinLow(pin) palClearLine(pin)
#define writePin(pin, level) ((level) ? (writePinHigh(pin)) : (writePinLow(pin)))

#define readPin(pin) palReadLine(pin)

#define togglePin(pin) palToggleLine(pin)

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e,\
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e,\
    k20, k21, k22, k23,	k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e,\
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e,\
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e,\
		k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a, k5b, k5c, k5d, k5e,\
		k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6a, k6b, k6c, k6d, k6e \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, }, \
    { k20, k21, k22, k23,	k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, }, \
		{ k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a, k5b, k5c, k5d, k5e, }, \
		{ k60, k61, k62, k63, k64, k65, k66, k67, k68, k69, k6a, k6b, k6c, k6d, KC_NO }, \
}


/* key matrix position */
typedef struct {
    uint8_t col;
    uint8_t row;
} keypos_t;

/* key event */
typedef struct {
    keypos_t key;
		uint16_t pressed;										//    bool     pressed;
    uint16_t time;
} keyevent_t;

static inline unsigned char IS_NOEVENT(keyevent_t event) { return event.time == 0 || (event.key.row == 255 && event.key.col == 255); }
static inline unsigned char IS_PRESSED(keyevent_t event) { return (!IS_NOEVENT(event) && event.pressed); }
static inline unsigned char IS_RELEASED(keyevent_t event) { return (!IS_NOEVENT(event) && !event.pressed); }

void keyb_init(void);

void keyboard_task(void);

#endif //_AMEKEYB_H
