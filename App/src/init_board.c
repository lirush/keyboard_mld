#include "init_board.h"
#include "MDR32F9Qx_rst_clk.h"
#include "systick.h"

void Clock_Configure(void)
{
	RST_CLK_HSEconfig(RST_CLK_HSE_ON);
  if (RST_CLK_HSEstatus() != SUCCESS)
  {
    while(1) ;
  }

  // CPU_C1_SEL = HSE
  RST_CLK_CPU_PLLconfig(RST_CLK_CPU_PLLsrcHSEdiv1, RST_CLK_CPU_PLLmul6);
  RST_CLK_CPU_PLLcmd(ENABLE);
  if (RST_CLK_CPU_PLLstatus() != SUCCESS)
  {
    while(1) ;
  }

  // CPU_C3_SEL = CPU_C2_SEL
  RST_CLK_CPUclkPrescaler(RST_CLK_CPUclkDIV1);
  // CPU_C2_SEL = PLL
  RST_CLK_CPU_PLLuse(ENABLE);
  // HCLK_SEL = CPU_C3_SEL
  RST_CLK_CPUclkSelection(RST_CLK_CPUclkCPU_C3);
	// Get Core Clock Frequency	
	SystemCoreClockUpdate();  
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTD | RST_CLK_PCLK_PORTE | RST_CLK_PCLK_PORTF, ENABLE);
	
	RST_CLK_PCLKcmd(RST_CLK_PCLK_IWDG,ENABLE);
	
	SysTickStart(48000);
}
