/**
 ******************************************************************************
 * @file	hal_pwr.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_PWR_H_
#define HAL_PWR_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"

#if (HAL_PWR_ENABLED == HAL_ENABLED)

#ifdef __cplusplus
 extern "C" {
#endif

bool
HAL_PWR_On(void);


#ifdef __cplusplus
}
#endif

#endif

#endif /* HAL_PWR_H_ */

/*****************************END OF FILE**************************************/
