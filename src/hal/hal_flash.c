/**
 ******************************************************************************
 * @file	hal_flash.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include "hal/hal_flash.h"

#define	HAL_FLASH_REG	FLASH		/*!< Reset Clock Control Register */

bool
HAL_FLASH_SetLatency(uint32_t latency)
{
	HAL_FLASH_REG->ACR = latency;

	return (HAL_FLASH_REG->ACR == latency);
}

