#ifndef _DEBOUNCE_H
#define _DEBOUNCE_H

#include "matrix.h"

void debounce_init(unsigned char num_rows);

void debounce(matrix_row_t raw[], matrix_row_t cooked[], uint8_t num_rows, bool changed);

#endif	//_DEBOUNCE_H

//// raw is the current key state
//// on entry cooked is the previous debounced state
//// on exit cooked is the current debounced state
//// changed is true if raw has changed since the last call

//bool debounce_active(void);

//void debounce_init(uint8_t num_rows);
