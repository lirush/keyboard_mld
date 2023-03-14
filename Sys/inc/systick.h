#ifndef __SYSTICK_H_
#define __SYSTICK_H_

#include <MDR32Fx.h>

extern volatile uint32_t Ticks;
extern volatile uint64_t ms_clk;

// System timer control
void SysTickStart(uint32_t ticks);
void SysTickStop(void);

// Delay function (systick-based)
void _delay_ms(const uint32_t ms);
void _delay_us(const uint32_t us);

#endif // __SYSTICK_H_
