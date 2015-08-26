/**
 ******************************************************************************
 * @file	bkp_sram.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include "bkp_sram.h"
#include "hal/hal.h"


void
BKP_SRAM_Init(void)
{
	/* Enable Power Clock */
	__PWR_CLK_ENABLE();

	/* access to the backup domain  */
	HAL_PWR_EnableBkUpAccess();

	/* Enable backup SRAM Clock */
	__BKPSRAM_CLK_ENABLE();
}

