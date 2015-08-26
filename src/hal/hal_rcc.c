/**
 ******************************************************************************
 * @file	hal_rcc.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */


#include "hal/hal_rcc.h"
#include "hal/hal_pwr.h"
#include "hal/hal_flash.h"

#if (HAL_RCC_ENABLED == HAL_ENABLED)

 /**
  * PLL_VCO		= HSE * (PLLN / PLLM)
  * SYSCLK		= PLL_CVO / PLLP
  * USB_OTG_CLK	= PLL_CVO / PLLQ
  *
  * Using max frequency for System Clock at 168Mz at HSE at 8MHz
  * and 48MHz for USB OTG/SDIO
  */
#define	HAL_RCC_PLLN			336
#define	HAL_RCC_PLLP			2
#define	HAL_RCC_PLLQ			7

#define HAL_RCC_HSE_STARTUP_TIMEOUT		0x500


#if !defined  (HSI_VALUE)
  #define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

uint32_t SystemCoreClock = 168000000;
__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

 void
 HAL_RCC_DeInitSystem(void)
 {
	 /* FPU settings ------------------------------------------------------------*/
	 #if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	 SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
	 #endif

	 /* Reset the RCC clock configuration to the default reset state ------------*/
	 /* Set HSION bit */
	  RCC->CR |= (uint32_t)0x00000001;

	 /* Reset CFGR register */
	  RCC->CFGR = 0x00000000;

	  /* Reset HSEON, CSSON and PLLON bits */
	  RCC->CR &= (uint32_t)0xFEF6FFFF;

	  /* Reset PLLCFGR register */
	  RCC->PLLCFGR = 0x24003010;

	  /* Reset HSEBYP bit */
	  RCC->CR &= (uint32_t)0xFFFBFFFF;

	  /* Disable all interrupts */
	  RCC->CIR = 0x00000000;

	  /* Configure the Vector Table location add offset address ------------------*/
	  SCB->VTOR = FLASH_BASE; /* Vector Table Relocation in Internal FLASH */
 }

 void
 HAL_RCC_InitSystem(void)
 {
	/* Set HSE on */
	RCC->CR |= ((uint32_t)RCC_CR_HSEON);

	/* Wait till HSE is ready */
	volatile uint32_t StartUpCounter = 0;

	while((RCC->CR & RCC_CR_HSERDY) != HAL_STAT_SET)
	{
		if((StartUpCounter > HAL_RCC_HSE_STARTUP_TIMEOUT))
			return;
	}

	/* Select regulator voltage output Scale 1 mode, System frequency up to 168 MHz */
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	PWR->CR |= PWR_CR_VOS;

	/* HCLK = SYSCLK / 1*/
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	/* PCLK2 = HCLK / 2*/
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

	/* PCLK1 = HCLK / 4*/
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

	/* Configure the main PLL clock source, multiplication and division factors. */
	uint32_t pllm = HSE_VALUE / 1000000;	/* Scale Clock to 1MHz */
	RCC->PLLCFGR = pllm | (HAL_RCC_PLLN << 6) | (((HAL_RCC_PLLP >> 1) -1) << 16) |
	                   (RCC_PLLCFGR_PLLSRC_HSE) | (HAL_RCC_PLLQ << 24);

	/* Enable the main PLL */
	RCC->CR |= RCC_CR_PLLON;

	/* Wait till the main PLL is ready */
	while((RCC->CR & RCC_CR_PLLRDY) == 0)
	{
	}
 }

 void
 HAL_RCC_Update(void)
 {
	  uint32_t tmp = 0, pllvco = 0, pllp = 2, pllsource = 0, pllm = 2;

	  /* Get SYSCLK source -------------------------------------------------------*/
	  tmp = RCC->CFGR & RCC_CFGR_SWS;

	  switch (tmp)
	  {
	    case 0x00:  /* HSI used as system clock source */
	      SystemCoreClock = HSI_VALUE;
	      break;
	    case 0x04:  /* HSE used as system clock source */
	      SystemCoreClock = HSE_VALUE;
	      break;
	    case 0x08:  /* PLL used as system clock source */

	      /* PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
	         SYSCLK = PLL_VCO / PLL_P
	         */
	      pllsource = (RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22;
	      pllm = RCC->PLLCFGR & RCC_PLLCFGR_PLLM;

	      if (pllsource != 0)
	      {
	        /* HSE used as PLL clock source */
	        pllvco = (HSE_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
	      }
	      else
	      {
	        /* HSI used as PLL clock source */
	        pllvco = (HSI_VALUE / pllm) * ((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6);
	      }

	      pllp = (((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >>16) + 1 ) *2;
	      SystemCoreClock = pllvco/pllp;
	      break;
	    default:
	      SystemCoreClock = HSI_VALUE;
	      break;
	  }
	  /* Compute HCLK frequency --------------------------------------------------*/
	  /* Get HCLK prescaler */
	  tmp = AHBPrescTable[((RCC->CFGR & RCC_CFGR_HPRE) >> 4)];
	  /* HCLK frequency */
	  SystemCoreClock >>= tmp;
 }

 uint32_t
 HAL_RCC_GetSystemClock(void)
 {
	 return SystemCoreClock;
 }

#endif

