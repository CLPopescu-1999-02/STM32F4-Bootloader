/**
 ******************************************************************************
 * @file	hal_exti.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_EXTI_H_
#define HAL_EXTI_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"
#include "hal_gpio.h"

#if (HAL_EXTI_ENABLED == HAL_ENABLED)

#ifdef __cplusplus
 extern "C" {
#endif

#define	HAL_EXTI_MAX_CHANNEL		23

 typedef enum
 {
	 HAL_EXTI_TRIGGER_RISING	= 1,
	 HAL_EXTI_TRIGGER_FALLING	= 2,
	 HAL_EXTI_TRIGGER_CHANGE	= 3,
 }hal_exti_trigger_t;

 typedef	void (*hal_exti_callback_t)(hal_gpio_pin_info_t *pp_pin);


 void
 HAL_EXTI_PinInit(hal_gpio_pin_info_t *pp_pin, hal_exti_trigger_t trigger, hal_exti_callback_t func);

 void
 HAL_EXTI_Init(uint32_t ch, hal_exti_trigger_t trigger, hal_exti_callback_t func);

 void
 HAL_EXTI_Enable(uint32_t ch);

 void
 HAL_EXTI_Disable(uint32_t ch);

#ifdef __cplusplus
}
#endif

#endif

#endif /* HAL_EXTI_H_ */

/*****************************END OF FILE**************************************/
