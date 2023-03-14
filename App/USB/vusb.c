#include "vusb.h"
#include "usbhw_MDR32F9x.h"
#include "systick.h"

#include <string.h>

struct keyboardHID_t {
      uint8_t modifiers;
			uint8_t rezerv;
      uint8_t key1;
      uint8_t key2;
      uint8_t key3;
			uint8_t key4;
			uint8_t key5;
			uint8_t key6;
};

void host_keyboard_send(report_keyboard_t *report)
{
	
	struct keyboardHID_t keyboardHID;
	
	keyboardHID.modifiers=report->mods;
		
	memcpy(&keyboardHID.key1,report->keys,6);
	
	USB_WriteEP(0x83,(U8*)&keyboardHID,sizeof(struct keyboardHID_t));
		_delay_ms(10);
}

void host_keyboard_init(void)
{
	struct keyboardHID_t keyboardHID;
	memset(&keyboardHID,0x00,sizeof(keyboardHID));
	USB_WriteEP(0x83,(U8*)&keyboardHID,sizeof(struct keyboardHID_t));
		_delay_ms(10);	
}
