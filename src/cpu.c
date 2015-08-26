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
#include "hal/hal.h"

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

 /**
  * @brief	Initial CPU early.
  * 		This function is called after reset and before initial data section.
  *
  * @note	Usually set CPU to highest frequency for fastest data initialization.
  */
 void
 CPU_InitEarly(void)
 {
	  // Set clock to highest frequency and have the rest of the initializations run faster.
	  HAL_RCC_DeInitSystem();

	  HAL_RCC_InitSystem();
 }

 /**
  * @brief	Initial CPU.
  * 		This function is called after initial data section.
  */
 void
 CPU_Init(void)
 {
	 /* Update System Core Clock variable according to Clock Register Values */
	 HAL_RCC_Update();
 }

 /**
  * @brief	Initial CPU Clock.
  */
 void
 CPU_ClockInit(void)
 {
 }

