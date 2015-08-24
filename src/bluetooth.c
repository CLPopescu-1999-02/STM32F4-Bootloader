/**
 ******************************************************************************
 * @file	bluetooth.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	24-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <string.h>
#include "bluetooth.h"

#define	BTH_EN_GPIO_PORT_NUM	3
#define	BTH_EN_GPIO_PORT		GPIOD
#define	BTH_EN_GPIO_PIN			GPIO_PIN_15

#define	BTH_RX_BUF_SIZE			64

static char gRxBuffer[RXBUFFERSIZE];
static char gTxBuffer[TXBUFFERSIZE];

static const char *STR_ERROR	= "ERROR";

static USART_HandleTypeDef gUsartHandle;
__IO ITStatus gUsartReady = RESET;

bool BTH_WaitForResponse(bool disableCmd)
{
	const char *response;

	response = BTH_Read();

	if(disableCmd)
		BTH_DisableCmd();

	return !strcmp(response, "OK");

}

void BTH_Init(void)
{
	/**
	 * Initial USART
	 */
	gUsartHandle.Instance			= USARTx;
	gUsartHandle.Init.BaudRate		= BTH_SPEED_DEFAULT;
	gUsartHandle.Init.WordLength	= USART_WORDLENGTH_8B;
	gUsartHandle.Init.StopBits		= USART_STOPBITS_1;
	gUsartHandle.Init.Parity		= USART_PARITY_NONE;
	gUsartHandle.Init.CLKPolarity	= USART_POLARITY_HIGH;
	gUsartHandle.Init.CLKLastBit	= USART_LASTBIT_DISABLE;
	gUsartHandle.Init.CLKPhase		= USART_PHASE_1EDGE;
	gUsartHandle.Init.Mode			= USART_MODE_TX_RX;

	HAL_USART_Init(&gUsartHandle);
}

void BTH_EnableCmd(void)
{
	HAL_GPIO_WritePin(BTH_EN_GPIO_PORT, BTH_EN_GPIO_PIN, SET);
}

void BTH_DisableCmd(void)
{
	HAL_GPIO_WritePin(BTH_EN_GPIO_PORT, BTH_EN_GPIO_PIN, RESET);
}


bool BTH_SetDeviceName(const char *name)
{
	BTH_EnableCmd();
	BTH_Write("AT+NAME=%s\r\n", name);
	return BTH_WaitForResponse(true);
}

bool BTH_SetSpeed(cpu_data speed)
{
	BTH_EnableCmd();
	BTH_Write("AT+UART=%d,0,0\r\n", speed);
	return BTH_WaitForResponse(true);
}

bool BTH_SetPassword(const char *password)
{
	BTH_EnableCmd();
	BTH_Write("AT+PSWD=%s\r\n", password);
	return BTH_WaitForResponse(true);
}

const char *
BTH_GetVersion(void)
{
	const char *ret;

	BTH_EnableCmd();
	BTH_Write("AT+VERSION?\r\n");
	ret = BTH_Read();
	BTH_DisableCmd();

	return ret;
}

void
BTH_Write(const char *format,...)
{
	va_list args;

	va_start(args, format);
	sprintf(gTxBuffer, format, args);
	va_end(args);

	gUsartHandle.State = HAL_USART_STATE_READY;
	if(HAL_USART_Transmit(&gUsartHandle, (uint8_t *)gTxBuffer, strlen(gTxBuffer), USART_TX_TIMEOUT) != HAL_OK)
	{

	}
}

const char *
BTH_Read(void)
{
	gUsartHandle.State = HAL_USART_STATE_READY;
	if(HAL_USART_Receive(&gUsartHandle, (uint8_t *)gRxBuffer, RXBUFFERSIZE, USART_RX_TIMEOUT) != HAL_OK)
	{
		return STR_ERROR;
	}

	return gRxBuffer;
}

/**
 * USART HAL Implementation
 */

/**
  * @brief UART MSP Initialization
  *        This function configures the hardware resources used in this example:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  *           - NVIC configuration for UART interrupt request enable
  * @param huart: UART handle pointer
  * @retval None
  */
void
HAL_USART_MspInit(USART_HandleTypeDef *hsuart)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

		(void)&hsuart;	/* Prevent compiler warning. */

	  /*##-1- Enable peripherals and GPIO Clocks #################################*/
	  /* Enable GPIO TX/RX clock */
	  USARTx_TX_GPIO_CLK_ENABLE();
	  USARTx_RX_GPIO_CLK_ENABLE();

	  /* Enable USART clock */
	  USARTx_CLK_ENABLE();

	  /*##-2- Configure peripheral GPIO ##########################################*/
	  /* UART TX GPIO pin configuration  */
	  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
	  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull      = GPIO_NOPULL;
	  GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	  GPIO_InitStruct.Alternate = USARTx_TX_AF;

	  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

	  /* UART RX GPIO pin configuration  */
	  GPIO_InitStruct.Pin 		= USARTx_RX_PIN;
	  GPIO_InitStruct.Alternate = USARTx_RX_AF;

	  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);

	  /*##-3- Configure the NVIC for UART ########################################*/
	  /* NVIC for USART */
	  HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
	  HAL_NVIC_EnableIRQ(USARTx_IRQn);
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(USART_HandleTypeDef *hsuart)
{
	(void)&hsuart;	/* Prevent compiler warning. */

  /*##-1- Reset peripherals ##################################################*/
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  /*##-2- Disable peripherals and GPIO Clocks #################################*/
  /* Configure UART Tx as alternate function  */
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  /* Configure UART Rx as alternate function  */
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);

  /*##-3- Disable the NVIC for UART ##########################################*/
  HAL_NVIC_DisableIRQ(USARTx_IRQn);
}
