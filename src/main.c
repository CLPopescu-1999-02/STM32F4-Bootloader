/**
 * @file	main.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 23, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include "hal/hal.h"

hal_gpio_pin_info_t led3;

int
main(void)
{
	// Send a greeting to the trace device (skipped on Release).
	trace_printf("Hello ARM World!");

	// At this stage the system clock should have already been configured
	// at high speed.
	trace_printf("System clock: %uHz\n", HAL_RCC_GetSystemClock);

	HAL_GPIO_PinInit(&led3, PD13);

	HAL_GPIO_Set(&led3);

	while(1)
	{
	}

	return 0;
}
