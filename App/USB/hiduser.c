/*----------------------------------------------------------------------------
 * U S B  -  K e r n e l
 *----------------------------------------------------------------------------
 * Name:    hiduser.c
 * Purpose: HID Custom User Module
 * Version: V1.20
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2009-2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------
 * History:
 *          V1.20 
 *          V1.00 Initial Version
 *----------------------------------------------------------------------------*/
#include <string.h>

#include "type.h"

#include "usb.h"
#include "hid.h"
#include "usbcfg_MDR32F9x.h"
#include "usbcore.h"
#include "hiduser.h"

#include "main.h"


U8 HID_Protocol;
U8 HID_IdleTime[HID_REPORT_NUM];

/*
 *  HID Get Report Request Callback
 *   Called automatically on HID Get Report Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_GetReport(unsigned int num) 
{
  /* ReportID = SetupPacket.wValue.WB.L; */
//	if(num==0)
	{
		switch (SetupPacket.wValue.WB.H) 
		{
			case HID_REPORT_INPUT:
//				GetInReport();
				//EP0Buf[0] = InReport;
				memcpy(EP0Buf, InReport, sizeof(InReport)); 
				break;
			case HID_REPORT_OUTPUT:
				return (__FALSE); // Not Supported
			case HID_REPORT_FEATURE:
//				GetFeatureReport();
				//EP0Buf[0] = FeatureReport;
				memcpy(EP0Buf, FeatureReport, sizeof(FeatureReport)); 
				break;
		}
	}
//	if(num==1)
//	{
//		switch (SetupPacket.wValue.WB.H) 
//		{
//			case HID_REPORT_INPUT:
//				GetInReport();
//				//EP0Buf[0] = InReport;
//				memcpy(EP0Buf, InReport2, sizeof(InReport)); 
//				break;
//			case HID_REPORT_OUTPUT:
//				return (__FALSE); // Not Supported
//			case HID_REPORT_FEATURE:
//				GetFeatureReport();
//				//EP0Buf[0] = FeatureReport;
//				memcpy(EP0Buf, FeatureReport2, sizeof(FeatureReport)); 
//				break;
//		}		
//	}
  return (__TRUE);
}


/*
 *  HID Set Report Request Callback
 *   Called automatically on HID Set Report Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_SetReport(void) 
{
  // ReportID = SetupPacket.wValue.WB.L;
		switch (SetupPacket.wValue.WB.H) 
		{
			case HID_REPORT_INPUT:
				return (__FALSE); // Not Supported
			case HID_REPORT_OUTPUT:
				//OutReport = EP0Buf[0];
				memcpy(OutReport, EP0Buf, sizeof(OutReport)); 
//				SetOutReport();
				break;
			case HID_REPORT_FEATURE:
				//FeatureReport = EP0Buf[0];
				memcpy(FeatureReport, EP0Buf, sizeof(&FeatureReport)); 
//				SetFeatureReport();
				break;
		}
  return (__FALSE);
}


/*
 *  HID Get Idle Request Callback
 *   Called automatically on HID Get Idle Request
 *    Parameters:      None (global SetupPacket and EP0Buf)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_GetIdle(void) 
{
  EP0Buf[0] = HID_IdleTime[SetupPacket.wValue.WB.L];
  return (__TRUE);
}


/*
 *  HID Set Idle Request Callback
 *   Called automatically on HID Set Idle Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_SetIdle(void) 
{
  HID_IdleTime[SetupPacket.wValue.WB.L] = SetupPacket.wValue.WB.H;
  /* Idle Handling if needed */
  return (__TRUE);
}


/*
 *  HID Get Protocol Request Callback
 *   Called automatically on HID Get Protocol Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_GetProtocol(void) 
{
  EP0Buf[0] = HID_Protocol;
  return (__TRUE);
}


/*
 *  HID Set Protocol Request Callback
 *   Called automatically on HID Set Protocol Request
 *    Parameters:      None (global SetupPacket)
 *    Return Value:    TRUE - Success, FALSE - Error
 */

BOOL HID_SetProtocol(void) 
{
  HID_Protocol = SetupPacket.wValue.WB.L;
  /* Protocol Handling if needed */
  return (__TRUE);
}
