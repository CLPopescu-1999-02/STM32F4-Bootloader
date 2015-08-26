/**
 ******************************************************************************
 * @file	bluetooth.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	24-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

/* Includes ------------------------------------------------------------------*/
#include <stdarg.h>
#include <stdbool.h>
#include "cpu.h"
#include "hal/hal.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	BTH_Mode_Comm,
	BTH_Mode_Cmd,
	BTH_Mode_Cmd_Default,
} BTH_Modes;

/* Exported constants --------------------------------------------------------*/
#define	BTH_MODEL				"HC-05"
#define	BTH_DEFAULT_COMM_SPEED	115200
#define	BTH_DEFAULT_CMD_SPEED	38400
#define	BTH_DEFAULT_NAME		"RAM-Engine"
#define	BTH_DEFAULT_PWD			"1234"

 /* Definition for USARTx clock resources */
 #define USARTx                           USART1
 #define USARTx_CLK_ENABLE()              __HAL_RCC_USART1_CLK_ENABLE();
 #define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()
 #define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOB_CLK_ENABLE()

 #define USARTx_FORCE_RESET()             __HAL_RCC_USART1_FORCE_RESET()
 #define USARTx_RELEASE_RESET()           __HAL_RCC_USART1_RELEASE_RESET()

 /* Definition for USARTx Pins */
 #define USARTx_TX_PIN                    GPIO_PIN_6
 #define USARTx_TX_GPIO_PORT              GPIOB
 #define USARTx_TX_AF                     GPIO_AF7_USART1
 #define USARTx_RX_PIN                    GPIO_PIN_7
 #define USARTx_RX_GPIO_PORT              GPIOB
 #define USARTx_RX_AF                     GPIO_AF7_USART1

 /* Definition for USARTx's NVIC */
 #define USARTx_IRQn                      USART1_IRQn
 #define USARTx_IRQHandler                USART1_IRQHandler

 /* Size of Transmission buffer */
 #define TXBUFFERSIZE                      64

 /* Size of Reception buffer */
 #define RXBUFFERSIZE                      TXBUFFERSIZE

#define USART_RX_TIMEOUT					100
#define USART_TX_TIMEOUT					100

#define	BTH_PWR_PORT						GPIOC
#define	BTH_PWR_PIN							GPIO_PIN_13
#define	BTH_PWR_CLK_EN						__GPIOC_CLK_ENABLE

#define	BTH_CMD_PORT						GPIOD
#define	BTH_CMD_PIN							GPIO_PIN_14
#define	BTH_CMD_CLK_EN						__GPIOD_CLK_ENABLE

#define	BTH_STAT_PORT						GPIOD
#define	BTH_STAT_PIN						GPIO_PIN_15
#define	BTH_STAT_CLK_EN						__GPIOD_CLK_ENABLE

 /* Exported macro ------------------------------------------------------------*/

 /* Exported functions ------------------------------------------------------- */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void BTH_Init(void);

void BTH_PowerOn(void);
void BTH_PowerOff(void);
void BTH_EnableCmd(void);
void BTH_DisableCmd(void);
bool BTH_IsPaired(void);

void BTH_HardReset(void);

void BTH_SetMode(BTH_Modes mode);
void BTH_SetSpeed(cpu_data speed);

bool BTH_SetNameCmd(const char *name);
bool BTH_SetSpeedCmd(cpu_data speed);
bool BTH_SetPasswordCmd(const char *password);

const char *
BTH_GetVersion(void);

void
BTH_Write(const char *format,...);

const char *
BTH_Read(void);

#ifdef __cplusplus
}
#endif

#endif /* BLUETOOTH_H_ */

/*****************************END OF FILE**************************************/
