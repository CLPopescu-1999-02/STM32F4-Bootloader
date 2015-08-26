/**
 ******************************************************************************
 * @file	hal_defines.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_DEFINES_H_
#define HAL_DEFINES_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_macro.h"

#ifdef __cplusplus
 extern "C" {
#endif

#ifndef	HAL_ENABLED
#define HAL_ENABLED				1u
#endif

#ifndef	HAL_DISABLED
#define HAL_DISABLED			0u
#endif

#ifndef	HAL_STAT_SET
#define HAL_STAT_SET			1u
#endif

#ifndef	HAL_STAT_RESET
#define HAL_STAT_RESET			0u
#endif

#ifdef __cplusplus
}
#endif

#endif /* HAL_DEFINES_H_ */

/*****************************END OF FILE**************************************/
