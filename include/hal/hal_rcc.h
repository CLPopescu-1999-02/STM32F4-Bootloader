/**
 ******************************************************************************
 * @file	hal_rcc.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_RCC_H_
#define HAL_RCC_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"

#if (HAL_RCC_ENABLED == HAL_ENABLED)

#ifdef __cplusplus
 extern "C" {
#endif

 void
 HAL_RCC_DeInitSystem(void);

 void
 HAL_RCC_InitSystem(void);

 void
 HAL_RCC_Update(void);

 uint32_t
 HAL_RCC_GetSystemClock(void);

#ifdef __cplusplus
}
#endif

#endif

#endif /* HAL_RCC_H_ */

/*****************************END OF FILE**************************************/
