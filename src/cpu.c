/**
 * @file	cpu.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 23, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include "cpu.h"

 /**
  * PLL_VCO		= HSE * (PLLN / PLLM)
  * SYSCLK		= PLL_CVO / PLLP
  * USB_OTG_CLK	= PLL_CVO / PLLQ
  *
  * Using max frequency for System Clock at 168Mz at HSE at 8MHz
  * and 48MHz for USB OTG/SDIO
  */
#define	CPU_RCC_CLK_PLLM			8U
#define	CPU_RCC_CLK_PLLN			336U
#define	CPU_RCC_CLK_PLLP			2U
#define	CPU_RCC_CLK_PLLQ			7U

 void
 CPU_SystemReset(void)
 {
	  /* FPU settings ------------------------------------------------------------*/
	  #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	    SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
	  #endif
	  /* Reset the RCC clock configuration to the default reset state ------------*/
	  /* Set HSION bit */
	  RCC->CR |= (cpu_data)0x00000001;

	  /* Reset CFGR register */
	  RCC->CFGR = 0x00000000;

	  /* Reset HSEON, CSSON and PLLON bits */
	  RCC->CR &= (cpu_data)0xFEF6FFFF;

	  /* Reset PLLCFGR register */
	  RCC->PLLCFGR = 0x24003010;

	  /* Reset HSEBYP bit */
	  RCC->CR &= (cpu_data)0xFFFBFFFF;

	  /* Disable all interrupts */
	  RCC->CIR = 0x00000000;

	  /* Configure the Vector Table location add offset address ------------------*/
	  SCB->VTOR = FLASH_BASE; /* Vector Table Relocation in Internal FLASH */
 }

 void
 CPU_ClockInit(void)
 {

	 /* Disable the HSE. */
	 RCC->CR &= ~(0x00010000);

	 /* Wait till HSE is ready */
	 while((RCC->CR & 0x00020000) != 0);

	 /* Disable the main PLL. */
	 RCC->CR &= ~(0x01000000);

	 /* Wait till PLL is ready */
	 while((RCC->CR & 0x02000000) != 0);

	 /**
	  * Configure the main PLL clock source, multiplication and division factors.
	  */
	 /* Set PLLM bit0-5*/
	 RCC->PLLCFGR &= ~(0x3F);
	 RCC->PLLCFGR |= (CPU_RCC_CLK_PLLM);

	 /* Set PLLN bit6-14 */
	 RCC->PLLCFGR &= ~(0x1FF << 6);
	 RCC->PLLCFGR |= (CPU_RCC_CLK_PLLN << 6);

	 /* Set PLLP bit16-17 */
	 RCC->PLLCFGR &= ~(0x3 << 16);
	 RCC->PLLCFGR |= (CPU_RCC_CLK_PLLP << 16);

	 /* Set PLLQ bit24-27 */
	 RCC->PLLCFGR &= ~(0xF << 24);
	 RCC->PLLCFGR |= (CPU_RCC_CLK_PLLQ << 24);

	 /* Set PLL Source bit22 to 1 (HSE) */
	 RCC->PLLCFGR |= (1 << 22);

	 /* Enable the main PLL. */
	 RCC->CR |= (0x01000000);

	 /* Wait till PLL is ready */
	 while((RCC->CR & 0x02000000) == 0);
 }

 extern void
 __attribute__((noreturn,weak))
 _start (void);

 void
 CPU_Reset(void)
 {
	 _start();
 }

 void ISR_Reset_Handler(void)
 {
 	CPU_Reset();
 }

