#ifndef __MDR32F9Qx_CONFIG_H
#define __MDR32F9Qx_CONFIG_H

#include "MDR32F9Qx_lib.h"
#include "stdint_ch.h"

#define USE_MDR1986VE9x

// Selet the header file for target microcontroller
#if defined ( USE_MDR1986VE9x )
	#include "MDR32Fx.h"
#elif defined (USE_MDR1986VE1T)
	#include "MDR1986VE1T.h"
#elif defined ( USE_MDR1986VE3 )
	#include "MDR1986VE3.h"
#endif

#define USE_JTAG_B 

// Target system parameters
// RST_CLK generators frequencies in HZ
#define HSI_Value       ((uint32_t)8000000)
#define HSE_Value       ((uint32_t)8000000)
#define HSE2_Value      ((uint32_t)25000000)
#define LSI_Value       ((uint32_t)40000)
#define LSE_Value       ((uint32_t)32768)

// RST_CLK frequencies startup timeouts settings
#define HSEonTimeOut    ((uint16_t)0x0600)
#define HSE2onTimeOut	((uint16_t)0x8000)
#define LSEonTimeOut    ((uint16_t)0x0600)
#define HSIonTimeOut    ((uint16_t)0x0600)
#define LSIonTimeOut    ((uint16_t)0x0600)
#define PLLCPUonTimeOut ((uint16_t)0x0600)
#define PLLUSBonTimeOut ((uint16_t)0x0600)

#define FLASH_PROG_FREQ_MHZ     (8.0)


// Known errors workaround control -------------------------------------------
#define WORKAROUND_MDR32F9QX_ERROR_0002


/* Select one of the following values of USE_ASSERT_INFO macro to control
   parameter checking in the Standard Peripheral Library drivers:
     0 - no parameter checks ("assert_param" macro is disabled);
     1 - check enabled, source file ID and line number are available;
     2 - check enabled, source file ID, line number and checking expression
         (as string) are available (increased code size).
*/
 #define USE_ASSERT_INFO    0 

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed user's function
  *   which gets the source file ID (see MDR32F9Qx_lib.h), line number and
  *   expression text (if USE_ASSERT_INFO == 2) of the call that failed. That
  *   function should not return. If expr is true, nothing is done.
  * @retval None
  */
#if (USE_ASSERT_INFO == 0)
  #define assert_param(expr) ((void)0)
#elif (USE_ASSERT_INFO == 1)
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__))
  void assert_failed(uint32_t file_id, uint32_t line);
#elif (USE_ASSERT_INFO == 2)
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed(ASSERT_INFO_FILE_ID, __LINE__, #expr))
  void assert_failed(uint32_t file_id, uint32_t line, const uint8_t* expr);
#else
  #error "Unsupported USE_ASSERT_INFO level"
#endif /* USE_ASSERT_INFO */

#if defined (__ICCARM__)
	#define __attribute__(name_section)
	#if defined (USE_MDR1986VE3) || defined (USE_MDR1986VE1T)
		#pragma section = "EXECUTABLE_MEMORY_SECTION"
		#define IAR_SECTION(section) @ section
	#elif defined (USE_MDR1986VE9x)
		#define IAR_SECTION(section)
	#endif
#endif
#if defined (__CMCARM__)
		#define __attribute__(name_section)
		#define IAR_SECTION(section)
#endif

#endif /* __MDR32F9Qx_CONFIG_H */
