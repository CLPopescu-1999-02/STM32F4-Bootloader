/**
 ******************************************************************************
 * @file	hal_flash.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_FLASH_H_
#define HAL_FLASH_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
bool
HAL_FLASH_SetLatency(uint32_t latency);


#ifdef __cplusplus
}
#endif

#endif /* HAL_FLASH_H_ */

/*****************************END OF FILE**************************************/
