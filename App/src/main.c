#include "main.h"
#include "MDR32F9Qx_usb_device.h"
#include "MDR32F9Qx_rst_clk.h"
#include "MDR32F9Qx_usb_handlers.h"
#include "usbhw_MDR32F9x.h"
#include "keymap.h"
#include "matrix.h"

#include "type.h"

#include "report.h"
#include "systick.h"

#include <string.h>

#include <math.h>
#include <stdio.h>

// Report Buffers
uint8_t InReport[HID_INPUT_REPORT_BYTES];
uint8_t OutReport[HID_OUTPUT_REPORT_BYTES]={0x00,0x00,0x09,0x00,0x00,0x00,0x00,0x00};			
uint8_t FeatureReport[HID_FEATURE_REPORT_BYTES];

void DeInitUsedPorts(void)
{
	PORT_DeInit(MDR_PORTA);
	PORT_DeInit(MDR_PORTB);
	PORT_DeInit(MDR_PORTF);
	PORT_DeInit(MDR_PORTE);
	PORT_DeInit(MDR_PORTD);
}

/*****Инициализация вывода ScrollLock*****
**Инициализирован отдельно потому что в порт D выведен JTAGB (pin 0-4)
**Прежде чем выводы порта D установить, нужно обнулить выводы jtag-а 
**(написано в мануале на данную микросхему)
**если этого не сделать "слетит" jtag.
**Защита от этого предусмотрено в стандартной библиотекой
**поэтому этот вывод инициализирован отдельно, посредствам стандартной библиотеки
*/
void InitLedScrollLock(void)
{
	PORT_InitTypeDef PortInitStructure;
	
	PortInitStructure.PORT_Pin = PORT_Pin_7;
  PortInitStructure.PORT_OE    = PORT_OE_OUT;
  PortInitStructure.PORT_FUNC = PORT_FUNC_PORT;
  PortInitStructure.PORT_MODE = PORT_MODE_DIGITAL;
  PortInitStructure.PORT_SPEED = PORT_SPEED_SLOW;
	
	PORT_Init(MDR_PORTD, &PortInitStructure);
}

void GetStateLedsKeyboard(void)
{		
		if(OutReport[0] & (1<<0)) MDR_PORTE->RXTX |= (1<<1);								//numlock
		else MDR_PORTE->RXTX &= ~(1<<1);
		if(OutReport[0] & (1<<1)) MDR_PORTE->RXTX |= (1<<0);								//capslock
		else MDR_PORTE->RXTX &= ~(1<<0);
	
		if(OutReport[0] & (1<<2)) PORT_SetBits(MDR_PORTD,PORT_Pin_7);				//scroll
		else PORT_ResetBits(MDR_PORTD,PORT_Pin_7);	
}

int main(void)
{
	Clock_Configure();
	
	InitHIDev=USE_KEYBOARD;
	
	USB_Init();
	USB_Connect(__TRUE);
	
	DeInitUsedPorts();
	
	InitLedScrollLock();
	
	keyb_init();
	
	while(1){

		keyboard_task();	
		
		GetStateLedsKeyboard();
	}
}
