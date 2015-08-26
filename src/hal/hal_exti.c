/**
 ******************************************************************************
 * @file	hal_exti.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */


#include "hal/hal_exti.h"
#include "stm32f4xx_macro.h"

#if (HAL_EXTI_ENABLED == HAL_ENABLED)

#define	HAL_EXTI_REG	EXTI			/*!< External Interrupt Register */

/**
 * @brief	List of pointer to GPIO PIN information.
 */
uint32_t		gExtiPinAddr[HAL_EXTI_MAX_CHANNEL];
hal_exti_callback_t	gExtiCallbackAddr[HAL_EXTI_MAX_CHANNEL];


/**********************************************************************************
 * EXTI Function Prototypes
 *********************************************************************************/
void
HAL_EXTI_Config(uint32_t ch, hal_exti_trigger_t trigger, hal_exti_callback_t func);
void
HAL_EXTI_SetTrigger(uint32_t ch, hal_exti_trigger_t trigger);
void
HAL_EXTI_SetCallback(uint32_t ch, hal_exti_callback_t func);
void
HAL_EXTI_ClearPending(uint32_t ch);


/**********************************************************************************
 * EXTI Initializations
 *********************************************************************************/
void
HAL_EXTI_PinInit(hal_gpio_pin_info_t *pp_pin, hal_exti_trigger_t trigger, hal_exti_callback_t func)
{
	if(gExtiPinAddr[pp_pin->pin_no] != 0)
	{
		HAL_TRACE("ERROR: EXTI%d already initialized!", pp_pin->pin_no);
	}
	else
	{
		/* Set used EXTI Pin address */
		gExtiPinAddr[pp_pin->pin_no] = (uint32_t)pp_pin;

		/* Initial configurations */
		HAL_EXTI_Init(pp_pin->pin_no, trigger, func);
	}
}

void
HAL_EXTI_Init(uint32_t ch, hal_exti_trigger_t trigger, hal_exti_callback_t func)
{
	/* Initial configurations */
	HAL_EXTI_Config(ch, trigger, func);
}

/**********************************************************************************
 * EXTI Configurations
 *********************************************************************************/
void
HAL_EXTI_Config(uint32_t ch, hal_exti_trigger_t trigger, hal_exti_callback_t func)
{
	HAL_EXTI_SetTrigger(ch, trigger);
	HAL_EXTI_SetCallback(ch, func);
}

void
HAL_EXTI_SetTrigger(uint32_t ch, hal_exti_trigger_t trigger)
{
	HAL_EXTI_REG->RTSR |= ((trigger & HAL_EXTI_TRIGGER_RISING) << ch);
	HAL_EXTI_REG->FTSR |= (((trigger & HAL_EXTI_TRIGGER_FALLING) >> 1) << ch);
}

void
HAL_EXTI_SetCallback(uint32_t ch, hal_exti_callback_t func)
{
	gExtiCallbackAddr[ch] = func;
}

/**********************************************************************************
 * EXTI Operations
 *********************************************************************************/
void
HAL_EXTI_Enable(uint32_t ch)
{
	HAL_EXTI_REG->IMR |= (1 << ch);
}

void
HAL_EXTI_Disable(uint32_t ch)
{
	HAL_EXTI_REG->IMR &= ~(1 << ch);
}

void
HAL_EXTI_ClearPending(uint32_t ch)
{
	HAL_EXTI_REG->PR |= (1 << ch);
}

/**********************************************************************************
 * EXTI Interrupt Service Routines
 *********************************************************************************/
/**
 * @brief	Handle EXTI Channel 0-15
 */
void
HAL_EXTI_IRQHandler(uint32_t ch)
{
	hal_exti_callback_t cb = gExtiCallbackAddr[ch];
	hal_gpio_pin_info_t *pin = 0;

	if(ch < HAL_GPIO_PINS_PER_PORT)
	{
		/* Handle EXTI from GPIO pin */
		pin = (hal_gpio_pin_info_t *)gExtiPinAddr[ch];

		/* Clear pending flag */
		HAL_EXTI_ClearPending(ch);

		/* Call back to request function */
		if(cb != 0)
			(*cb)(pin);
	}
	else
	{
		HAL_EXTI_ClearPending(ch);
	}
}

/**
 * @brief	Handle EXTI Channel 0
 */
void
ISR_EXTI0_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(0);
}

/**
 * @brief	Handle EXTI Channel 1
 */
void
ISR_EXTI1_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(1);
}

/**
 * @brief	Handle EXTI Channel 2
 */
void
ISR_EXTI2_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(2);
}

/**
 * @brief	Handle EXTI Channel 3
 */
void
ISR_EXTI3_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(3);
}

/**
 * @brief	Handle EXTI Channel 4
 */
void
ISR_EXTI4_IRQHandler(void)
{
	HAL_EXTI_IRQHandler(4);
}

/**
 * @brief	Handle EXTI Channel 5-9
 */
void
ISR_EXTI9_5_IRQHandler(void)
{
	register uint32_t reg;

	reg = CPU_CTZ(EXTI->PR);	/* Check pending channel */
	HAL_EXTI_IRQHandler(reg);
}

/**
 * @brief	Handle EXTI Channel 10-15
 */
void
ISR_EXTI15_10_IRQHandler(void)
{
	register uint32_t reg;

	reg = CPU_CTZ(EXTI->PR);	/* Check pending channel */
	HAL_EXTI_IRQHandler(reg);
}

#endif
