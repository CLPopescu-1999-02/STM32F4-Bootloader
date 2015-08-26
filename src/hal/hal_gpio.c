/**
 ******************************************************************************
 * @file	hal_gpio.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include "hal/hal_gpio.h"

#if (HAL_GPIO_ENABLED == HAL_ENABLED)

#define	HAL_GPIO_RESERVED_PIN_ADDR		0xFFFFFFFFUL

#define	HAL_GPIO_REG(x)					((GPIO_TypeDef *)(x))

/**
 * @brief	List of pointer to GPIO PIN information.
 */
uint32_t	gPinAddr[HAL_GPIO_MAX_PORTS][HAL_GPIO_PINS_PER_PORT];


/**********************************************************************************
 * GPIO Pin Initializations
 *********************************************************************************/
void
HAL_GPIO_PinInit(hal_gpio_pin_info_t *pp_info, hal_gpio_pin_t p_pin)
{
	hal_gpio_pin_info_t *ptr = (hal_gpio_pin_info_t *)(&gPinAddr + p_pin);

	if((uint32_t)ptr == HAL_GPIO_RESERVED_PIN_ADDR)
	{
		HAL_TRACE("ERROR: Trying to initial reserved GPIO Pin!");
	}
	else if(ptr != 0)
	{
		HAL_TRACE("ERROR: Trying to initial used GPIO Pin!");
	}
	else
	{
		pp_info->port_no	= p_pin / HAL_GPIO_PINS_PER_PORT;
		pp_info->pin_no		= p_pin % HAL_GPIO_PINS_PER_PORT;

		pp_info->port_addr	= HAL_GPIO_PORT_BASE + HAL_GPIO_PORT_SIZE * pp_info->port_no;

	}
}

void
HAL_GPIO_ClkEn(hal_gpio_pin_info_t *pp_info)
{
	RCC->AHB1ENR	|= (1 << pp_info->port_no);
}

/**********************************************************************************
 * GPIO Pin Configurations
 *********************************************************************************/
void
HAL_GPIO_PinConfig(hal_gpio_pin_info_t *pp_info, hal_gpio_config_t *config)
{
	HAL_GPIO_SetMode(pp_info, config->mode);

	if(config->mode != HAL_GPIO_MODE_INPUT)
	{
		HAL_GPIO_SetOutputType(pp_info, config->otype);
		HAL_GPIO_SetSpeed(pp_info, config->speed);
	}

	HAL_GPIO_SetPullupPulldown(pp_info, config->pupd);
}

void
HAL_GPIO_SetMode(hal_gpio_pin_info_t *pp_info, hal_gpio_mode_t mode)
{
	HAL_GPIO_REG(pp_info->port_addr)->MODER |= (mode << pp_info->pin_no * 2);
}

void
HAL_GPIO_SetOutputType(hal_gpio_pin_info_t *pp_info, hal_gpio_output_t otype)
{
	HAL_GPIO_REG(pp_info->port_addr)->OTYPER |= (otype << pp_info->pin_no);
}

void
HAL_GPIO_SetSpeed(hal_gpio_pin_info_t *pp_info, hal_gpio_speed_t speed)
{
	HAL_GPIO_REG(pp_info->port_addr)->OSPEEDR |= (speed << pp_info->pin_no * 2);
}

void
HAL_GPIO_SetPullupPulldown(hal_gpio_pin_info_t *pp_info, hal_gpio_pupd_t pupd)
{
	HAL_GPIO_REG(pp_info->port_addr)->PUPDR |= (pupd << pp_info->pin_no * 2);
}

void
HAL_GPIO_SetAlternate(hal_gpio_pin_info_t *pp_info, hal_gpio_af_t af)
{
	HAL_GPIO_REG(pp_info->port_addr)->AFR[pp_info->pin_no >> 3] |= (af << (pp_info->pin_no * 4) % 32);
}

/**********************************************************************************
 * GPIO Pin Operations
 *********************************************************************************/

/**
 * @brief	GPIO Pin set.
 */
void
HAL_GPIO_Set(hal_gpio_pin_info_t *pp_info)
{
	HAL_GPIO_REG(pp_info->port_addr)->BSRR |= (0x01 << pp_info->pin_no);
}

/**
 * @brief	GPIO Pin reset.
 */
void
HAL_GPIO_Reset(hal_gpio_pin_info_t *pp_info)
{
	HAL_GPIO_REG(pp_info->port_addr)->BSRR |= (0x0100 << pp_info->pin_no);
}

/**
 * @brief	GPIO Pin toggle.
 */
void
HAL_GPIO_Toggle(hal_gpio_pin_info_t *pp_info)
{
	HAL_GPIO_REG(pp_info->port_addr)->ODR ^= (0x01 << pp_info->pin_no);
}

#endif
