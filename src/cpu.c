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
#include "stm32f4xx_hal.h"

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
	  SystemInit();

	  CPU_ClockInit();
 }

 /**
  * @brief	Initial CPU.
  * 		This function is called after initial data section.
  */
 void
 CPU_Init(void)
 {
	 /* Update System Core Clock variable according to Clock Register Values */
	 SystemCoreClockUpdate();
 }

 /**
  * @brief	Initial CPU Clock.
  */
 void
 CPU_ClockInit(void)
 {
	  RCC_ClkInitTypeDef RCC_ClkInitStruct;
	  RCC_OscInitTypeDef RCC_OscInitStruct;

	  // Enable Power Control clock
	  __PWR_CLK_ENABLE();

	  // The voltage scaling allows optimizing the power consumption when the
	  // device is clocked below the maximum system frequency, to update the
	  // voltage scaling value regarding system frequency refer to product
	  // datasheet.
	  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

	  // Enable HSE Oscillator and activate PLL with HSE as source
	  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;

	  // This assumes the HSE_VALUE is a multiple of 1MHz. If this is not
	  // your case, you have to recompute these PLL constants.
	  RCC_OscInitStruct.PLL.PLLM = (HSE_VALUE/1000000u);
	  RCC_OscInitStruct.PLL.PLLN = 336;
	  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	  RCC_OscInitStruct.PLL.PLLQ = 7;
	  HAL_RCC_OscConfig(&RCC_OscInitStruct);

	  // Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2
	  // clocks dividers
	  RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK
	      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
	  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
 }

