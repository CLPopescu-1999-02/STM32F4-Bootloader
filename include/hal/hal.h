/**
 ******************************************************************************
 * @file	hal.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_H_
#define HAL_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"

#ifdef __cplusplus
 extern "C" {
#endif

#if	(HAL_RCC_ENABLED == HAL_ENABLED)
#include "hal_rcc.h"
#endif
#if	(HAL_PWR_ENABLED == HAL_ENABLED)
#include "hal_pwr.h"
#endif
#if	(HAL_BKP_SRAM_ENABLED == HAL_ENABLED)
#include "hal_bkp_sram.h"
#endif
#if	(HAL_GPIO_ENABLED == HAL_ENABLED)
#include "hal_gpio.h"
#endif
#if	(HAL_EXTI_ENABLED == HAL_ENABLED)
#include "hal_exti.h"
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_H_ */

/*****************************END OF FILE**************************************/
