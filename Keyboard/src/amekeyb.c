#include "incudes.h"
#include "matrix.h"
#include "timer_a.h"
#include "led.h"
#include "vusb.h"

/** \brief is_keyboard_master
 *
 * FIXME: needs doc
 */
__attribute__((weak)) bool is_keyboard_master(void) { return true; }

/** \brief should_process_keypress
 *
 * Override this function if you have a condition where keypresses processing should change:
 *   - splits where the slave side needs to process for rgb/oled functionality
 */
__attribute__((weak)) bool should_process_keypress(void) { return is_keyboard_master(); }

void keyb_init(void)
{
	timer_init();
	matrix_init();
	led_init_ports();
	host_keyboard_init();										//first send is zero
}

void keyboard_task(void)
{
	static matrix_row_t matrix_prev[MATRIX_ROWS];
	matrix_row_t        matrix_row    = 0;
	matrix_row_t        matrix_change = 0;	
	
	matrix_scan();
	
	if(should_process_keypress())
	{
        for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
            matrix_row    = matrix_get_row(r);
            matrix_change = matrix_row ^ matrix_prev[r];
            if (matrix_change) {
                matrix_row_t col_mask = 1;
                for (uint8_t c = 0; c < MATRIX_COLS; c++, col_mask <<= 1) {
                    if (matrix_change & col_mask) {
                       action_exec((keyevent_t){
                            .key = (keypos_t){.row = r, .col = c}, .pressed = (matrix_row & col_mask), .time = (timer_read() | 1) /* time should not be 0 */
                        });
                        matrix_prev[r] ^= col_mask;
                    }
                }
            }
        }
	}
	
}
