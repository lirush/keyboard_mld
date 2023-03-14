#ifndef _MAIN_H
#define _MAIN_H

#include "MDR32Fx.h"

#include "init_board.h"

#include "usbdesc.h"

// Report Buffers
extern uint8_t InReport[HID_INPUT_REPORT_BYTES];
extern uint8_t OutReport[HID_OUTPUT_REPORT_BYTES];			
extern uint8_t FeatureReport[HID_FEATURE_REPORT_BYTES];	

#endif //_MAIN_H
