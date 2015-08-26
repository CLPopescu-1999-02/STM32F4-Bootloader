/**
 ******************************************************************************
 * @file	time.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include "time.h"
#include "stm32f4xx_hal.h"

void
ISR_SysTick_Handler(void)
{
	HAL_IncTick();
}


void
TIME_Init(void)
{
	/* Initial sysem tick */
	HAL_Init();

	HAL_InitTick(0);
}

cpu_data
TIME_GetTicks(void)
{
	return HAL_GetTick();
}

cpu_data
TIME_GetMs(void)
{
	return HAL_GetTick();
}


void
TIME_Delay(cpu_data ticks)
{
	ticks += HAL_GetTick();

	while(HAL_GetTick() < ticks );
}

void
TIME_DelayMs(cpu_data ms)
{
	cpu_data ticks = HAL_GetTick() + ms;

	while(HAL_GetTick() < ticks );
}
