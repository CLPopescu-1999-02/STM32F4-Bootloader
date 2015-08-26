/**
 ******************************************************************************
 * @file	hal_gpio.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	26-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HAL_GPIO_H_
#define HAL_GPIO_H_

/* Includes ------------------------------------------------------------------*/
#include "hal_conf.h"

#if (HAL_GPIO_ENABLED == HAL_ENABLED)

#ifdef __cplusplus
 extern "C" {
#endif

 /**********************************************************************************
  * GPIO Pin Types
  *********************************************************************************/
 /**
  * @brief	List of available IO Pin
  */
 typedef enum
 {
 	PA0,
 	PA1,
 	PA2,
 	PA3,
 	PA4,
 	PA5,
 	PA6,
 	PA7,
 	PA8,
 	PA9,
 	PA10,
 	PA11,
 	PA12,
 	PA13,
 	PA14,
 	PA15,
 	PB0,
 	PB1,
 	PB2,
 	PB3,
 	PB4,
 	PB5,
 	PB6,
 	PB7,
 	PB8,
 	PB9,
 	PB10,
 	PB11,
 	PB12,
 	PB13,
 	PB14,
 	PB15,
 	PC0,
 	PC1,
 	PC2,
 	PC3,
 	PC4,
 	PC5,
 	PC6,
 	PC7,
 	PC8,
 	PC9,
 	PC10,
 	PC11,
 	PC12,
 	PC13,
 	PC14,
 	PC15,
 	PD0,
 	PD1,
 	PD2,
 	PD3,
 	PD4,
 	PD5,
 	PD6,
 	PD7,
 	PD8,
 	PD9,
 	PD10,
 	PD11,
 	PD12,
 	PD13,
 	PD14,
 	PD15,
 #if defined(GPIOE)
 	PE0,
 	PE1,
 	PE2,
 	PE3,
 	PE4,
 	PE5,
 	PE6,
 	PE7,
 	PE8,
 	PE9,
 	PE10,
 	PE11,
 	PE12,
 	PE13,
 	PE14,
 	PE15,
 #endif
 #if defined(GPIOF)
 	PF0,
 	PF1,
 	PF2,
 	PF3,
 	PF4,
 	PF5,
 	PF6,
 	PF7,
 	PF8,
 	PF9,
 	PF10,
 	PF11,
 	PF12,
 	PF13,
 	PF14,
 	PF15,
 #endif
 #if defined(GPIOG)
 	PG0,
 	PG1,
 	PG2,
 	PG3,
 	PG4,
 	PG5,
 	PG6,
 	PG7,
 	PG8,
 	PG9,
 	PG10,
 	PG11,
 	PG12,
 	PG13,
 	PG14,
 	PG15,
 #endif
 #if defined(GPIOH)
 	PH0,
 	PH1,
 	PH2,
 	PH3,
 	PH4,
 	PH5,
 	PH6,
 	PH7,
 	PH8,
 	PH9,
 	PH10,
 	PH11,
 	PH12,
 	PH13,
 	PH14,
 	PH15,
 #endif
 #if defined(GPIOI)
 	PI0,
 	PI1,
 	PI2,
 	PI3,
 	PI4,
 	PI5,
 	PI6,
 	PI7,
 	PI8,
 	PI9,
 	PI10,
 	PI11,
 	PI12,
 	PI13,
 	PI14,
 	PI15,
 #endif
 } hal_gpio_pin_t;

 typedef enum
 {
	 HAL_GPIO_MODE_OUTPUT,
	 HAL_GPIO_MODE_INPUT,
	 HAL_GPIO_MODE_ALTERNATE,
 } hal_gpio_mode_t;

 typedef enum
 {
	 HAL_GPIO_OUTPUT_PP,
	 HAL_GPIO_OUTPUT_OD,
 } hal_gpio_output_t;

 typedef enum
 {
	 HAL_GPIO_SPEED_LOW,
	 HAL_GPIO_SPEED_MEDIUM,
	 HAL_GPIO_SPEED_FAST,
	 HAL_GPIO_SPEED_HIGH,
 } hal_gpio_speed_t;

 typedef enum
 {
	 HAL_GPIO_PUPD_NONE,
	 HAL_GPIO_PUPD_UP,
	 HAL_GPIO_PUPD_DOWN,
 } hal_gpio_pupd_t;

 typedef enum
 {
	 HAL_GPIO_AF0,
	 HAL_GPIO_AF1,
	 HAL_GPIO_AF2,
	 HAL_GPIO_AF3,
	 HAL_GPIO_AF4,
	 HAL_GPIO_AF5,
	 HAL_GPIO_AF6,
	 HAL_GPIO_AF7,
	 HAL_GPIO_AF8,
	 HAL_GPIO_AF9,
	 HAL_GPIO_AF10,
	 HAL_GPIO_AF11,
	 HAL_GPIO_AF12,
	 HAL_GPIO_AF13,
	 HAL_GPIO_AF14,
	 HAL_GPIO_AF15,
 } hal_gpio_af_t;

 typedef enum
 {
	 HAL_GPIO_STAT_RESET	= 0,
	 HAL_GPIO_STAT_SET		= 1,
 } hal_gpio_stat_t;

 typedef struct
 {
	 hal_gpio_mode_t		mode;
	 hal_gpio_output_t		otype;
	 hal_gpio_speed_t		speed;
	 hal_gpio_pupd_t		pupd;
	 hal_gpio_af_t			af;
 } hal_gpio_config_t;

 typedef struct
 {
	 uint8_t		pin_no;
	 uint8_t		port_no;
	 uint32_t		port_addr;
 } hal_gpio_pin_info_t;

 /**********************************************************************************
  * GPIO Pin Defines
  *********************************************************************************/

#define HAL_GPIO_PORT_BASE			GPIOA_BASE						// First port base address
#define HAL_GPIO_PORT_SIZE			(GPIOB_BASE - GPIOA_BASE)		// Port size

/**
 * @details	number of GPIO port declaration
 */
#if defined(GPIOI)
	#define HAL_GPIO_MAX_PORTS		9
#elif defined(GPIOH)
	#define HAL_GPIO_MAX_PORTS		8
#elif defined(GPIOG)
	#define HAL_GPIO_MAX_PORTS		7
#elif defined(GPIOF)
	#define HAL_GPIO_MAX_PORTS		6
#elif defined(GPIOE)
	#define HAL_GPIO_MAX_PORTS		5
#else
	#define HAL_GPIO_MAX_PORTS		4
#endif

/**
 * @details	number of GPIO pin per port declaration
 */
#define HAL_GPIO_PINS_PER_PORT		16

 /**********************************************************************************
  * GPIO Pin Functions
  *********************************************************************************/
 void
 HAL_GPIO_Init(hal_gpio_pin_info_t *pp_info, hal_gpio_pin_t p_pin);
 void
 HAL_GPIO_ClkEn(hal_gpio_pin_info_t *pp_info);

 void
 HAL_GPIO_PinConfig(hal_gpio_pin_info_t *pp_info, hal_gpio_config_t *config);
 void
 HAL_GPIO_SetMode(hal_gpio_pin_info_t *pp_info, hal_gpio_mode_t mode);
 void
 HAL_GPIO_SetOutputType(hal_gpio_pin_info_t *pp_info, hal_gpio_output_t otype);
 void
 HAL_GPIO_SetSpeed(hal_gpio_pin_info_t *pp_info, hal_gpio_speed_t speed);
 void
 HAL_GPIO_SetPullupPulldown(hal_gpio_pin_info_t *pp_info, hal_gpio_pupd_t pupd);
 void
 HAL_GPIO_SetAlternate(hal_gpio_pin_info_t *pp_info, hal_gpio_af_t af);

 void
 HAL_GPIO_Set(hal_gpio_pin_info_t *pp_info);
 void
 HAL_GPIO_Reset(hal_gpio_pin_info_t *pp_info);
 void
 HAL_GPIO_Toggle(hal_gpio_pin_info_t *pp_info);
 hal_gpio_stat_t
 HAL_GPIO_Read(hal_gpio_pin_info_t *pp_info);


#ifdef __cplusplus
}
#endif

#endif

#endif /* HAL_GPIO_H_ */

/*****************************END OF FILE**************************************/
