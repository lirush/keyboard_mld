#ifndef _PAL_H
#define _PAL_H

/**
* @brief   After reset state.
* @details The state itself is not specified and is architecture dependent,
*          it is guaranteed to be equal to the after-reset state. It is
*          usually an input state.
*/
#define PAL_MODE_RESET                  0U

/**
* @brief   Safe state for <b>unconnected</b> pads.
* @details The state itself is not specified and is architecture dependent,
*          it may be mapped on @p PAL_MODE_INPUT_PULLUP,
*          @p PAL_MODE_INPUT_PULLDOWN or @p PAL_MODE_OUTPUT_PUSHPULL for
*          example.
*/
#define PAL_MODE_UNCONNECTED            1U

/**
* @brief   Regular input high-Z pad.
*/
#define PAL_MODE_INPUT                  2U

/**
* @brief   Input pad with weak pull up resistor.
*/
#define PAL_MODE_INPUT_PULLUP           1U

/**
* @brief   Input pad with weak pull down resistor.
*/
#define PAL_MODE_INPUT_PULLDOWN         4U

/**
* @brief   Analog input mode.
*/
#define PAL_MODE_INPUT_ANALOG           5U

/**
* @brief   Push-pull output pad.
*/
#define PAL_MODE_OUTPUT_PUSHPULL        6U

/**
* @brief   Open-drain output pad.
*/
#define PAL_MODE_OUTPUT_OPENDRAIN       7U
/** @} */

/**
* @brief   Slow front pad.
*/
#define PAL_MODE_SLOW_FRONT			        1U
/** @} */

/**
* @brief   Fast front pad.
*/
#define PAL_MODE_FAST_FRONT			        2U
/** @} */

/**
* @brief   Max fast front pad.
*/
#define PAL_MODE_MAXFAST_FRONT			    3U
/** @} */

#define PAL_PORT_BIT_PULL(n) ((ioportmask_t)(1U << (n+16)))

#define PAL_PORT_BIT_PWR(n,mode) ((ioportmask_t)(mode << (n*2)))				//slow front

#define PAL_PORT_BIT_PWR_FF(n) ((ioportmask_t)(2U << (n*2)))								//fast front

#define PAL_PORT_BIT_PWR_MFF(n) ((ioportmask_t)(3U << (n*2)))								//mast fast front

#define PAL_PORT_BIT(n) ((ioportmask_t)(1U << (n)))

#define palReadPort(port) ((void)(port), 0U)

#define palReadLatch(port) ((void)(port), 0U)

#define palWritePort(port, bits) ((void)(port), (void)(bits))

#define palClearPort(port, bits)  (port->RXTX &= ~bits)

#define palClearPad(port, pad) palClearPort(port, PAL_PORT_BIT(pad))

#define palSetGroupOutEn(port, mask, offset, mode)	(port->OE |= mask)

#define palClearGroupOutEn(port, mask, offset, mode)	(port->OE &= ~mask)

#define palSetGroupMode(port, mask, offset, mode)	(port->FUNC |= mask)

#define palSetGroupPull(port, mask, offset, mode)	(port->PULL |= mask)

#define palClearGroupPull(port, mask, offset, mode)	(port->PULL &= ~mask)

#define palSetGroupDigital(port, mask)	(port->ANALOG |= mask)

#define palSetGroupPower(port, mask)	(port->PWR |= mask)

#define palReadPort(port) ((void)(port), 0U)

#define palSetPadMode(port, pad, mode) palSetGroupMode(port, PAL_PORT_BIT(pad), 0U, mode)

#define palSetPadOutEn(port, pad, mode) palSetGroupOutEn(port, PAL_PORT_BIT(pad), 0U, mode)

#define palClearPadOutEn(port, pad, mode) palClearGroupOutEn(port, PAL_PORT_BIT(pad), 0U, mode)

#define palSetPadPull(port, pad, mode) palSetGroupPull(port, PAL_PORT_BIT_PULL(pad), 0x10U, mode)

#define palClearPadPull(port, pad, mode) palClearGroupPull(port, PAL_PORT_BIT_PULL(pad), 0x10U, mode)

#define palSetPadDigital(port, pad)	palSetGroupDigital(port, PAL_PORT_BIT(pad))

#define palSetPadPower(port, pad)	palSetGroupPower(port, PAL_PORT_BIT_PWR(pad,PAL_MODE_SLOW_FRONT))

#define palReadPad(port, pad) ((port->RXTX & (1<<pad))>>pad)//((palReadPort(port) >> (pad)) & 1U)

#define palClearLine(line) palClearPad(PAL_PORT(line), PAL_PAD(line))

#define palReadLine(line) palReadPad(PAL_PORT(line), PAL_PAD(line))

#define palSetLineMode(line, mode) palSetPadMode(PAL_PORT(line), PAL_PAD(line), mode)

#define palSetLineOutEn(line, mode) palSetPadOutEn(PAL_PORT(line), PAL_PAD(line), mode)

#define palClearLineOutEn(line, mode) palClearPadOutEn(PAL_PORT(line), PAL_PAD(line), mode)

#define palSetLinePull(line, mode) palSetPadPull(PAL_PORT(line), PAL_PAD(line), mode)

#define palClearLinePull(line, mode) palClearPadPull(PAL_PORT(line), PAL_PAD(line), mode)

#define palSetLineDigital(line)	palSetPadDigital(PAL_PORT(line), PAL_PAD(line))

#define palSetLinePower(line) palSetPadPower(PAL_PORT(line),PAL_PAD(line))

#endif //_PAL_H
