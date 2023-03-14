#ifndef _VUSB_H
#define _VUSB_H

#include "report.h"

void host_keyboard_send(report_keyboard_t *report);
void host_keyboard_init(void);

#endif	//_VUSB_H
