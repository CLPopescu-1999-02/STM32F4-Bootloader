/**
 ******************************************************************************
 * @file	hal_conf.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_CONF_H_
#define HAL_CONF_H_

/* Includes ------------------------------------------------------------------*/
#include "hal/hal_defines.h"
#include "stm32f407xx.h"

#ifdef __cplusplus
 extern "C" {
#endif



#ifndef	HAL_USED_ENABLE
#define HAL_USED_ENABLE			HAL_ENABLED
#endif

#if (HAL_USED_ENABLE == HAL_ENABLED)

#define HAL_RCC_ENABLED			HAL_ENABLED
#define HAL_PWR_ENABLED			HAL_ENABLED
#define HAL_GPIO_ENABLED		HAL_ENABLED
#define HAL_EXTI_ENABLED		HAL_ENABLED

#if defined(TRACE)
 extern int
 trace_printf(const char* format, ...);
#else
 static inline int
 trace_printf(const char* format, ...)
 {

 }
#endif

#define HAL_TRACE				trace_printf
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_CONF_H_ */

/*****************************END OF FILE**************************************/
