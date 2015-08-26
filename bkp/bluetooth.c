/**
 ******************************************************************************
 * @file	bluetooth.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	24-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include <stdio.h>
#include <string.h>
#include "bluetooth.h"
#include "bkp_sram.h"
#include "time.h"
#include "diag/Trace.h"
#include "stm32f4xx_macro.h"

#define	BTH_RX_BUF_SIZE			64
#define	BTH_ON_OFF_DELAY_MS		10

static char gRxBuffer[RXBUFFERSIZE];
static char gTxBuffer[TXBUFFERSIZE];
static char *ptrRxBuffer;

static UART_HandleTypeDef gUartHandle;
static DMA_HandleTypeDef gDMAHandle;

__IO ITStatus gUARTReady = RESET;

bool BTH_WaitForResponse(void)
{
	const char *response;

	response = BTH_Read();

	return !strcmp(response, "OK");

}

void BTH_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Initial Power pin (output) */
	GPIO_InitStruct.Pin       = BTH_PWR_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	HAL_GPIO_Init(BTH_PWR_PORT, &GPIO_InitStruct);
	BTH_PWR_CLK_EN();

	/* Initial Command pin (output) */
	GPIO_InitStruct.Pin       = BTH_CMD_PIN;
	HAL_GPIO_Init(BTH_CMD_PORT, &GPIO_InitStruct);
	BTH_CMD_CLK_EN();

	/* Initial State pin (input) */
	GPIO_InitStruct.Pin       = BTH_STAT_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
	HAL_GPIO_Init(BTH_STAT_PORT, &GPIO_InitStruct);
	BTH_STAT_CLK_EN();
}

void BTH_PowerOn(void)
{
	HAL_GPIO_WritePin(BTH_PWR_PORT, BTH_PWR_PIN, SET);

	TIME_DelayMs(BTH_ON_OFF_DELAY_MS);
}

void BTH_PowerOff(void)
{
	HAL_GPIO_WritePin(BTH_PWR_PORT, BTH_PWR_PIN, RESET);
	TIME_DelayMs(BTH_ON_OFF_DELAY_MS);
}

void BTH_EnableCmd(void)
{
	HAL_GPIO_WritePin(BTH_CMD_PORT, BTH_CMD_PIN, SET);
	TIME_DelayMs(BTH_ON_OFF_DELAY_MS);
}

void BTH_DisableCmd(void)
{
	HAL_GPIO_WritePin(BTH_CMD_PORT, BTH_CMD_PIN, RESET);
	TIME_DelayMs(BTH_ON_OFF_DELAY_MS);
}

bool BTH_IsPaired(void)
{
	return (HAL_GPIO_ReadPin(BTH_STAT_PORT, BTH_STAT_PIN) != GPIO_PIN_RESET);
}

void BTH_SetMode(BTH_Modes mode)
{
	switch(mode)
	{
	case BTH_Mode_Cmd:
		/**
		 * Using command mode with same speed as communication mode.
		 * This method require to power on before enable command mode.
		 */
		/* Power off */
		BTH_PowerOff();

		/* Disable command mode */
		BTH_DisableCmd();

		/* Power on */
		BTH_PowerOn();

		/* Enable command mode */
		BTH_EnableCmd();
		break;
	case BTH_Mode_Cmd_Default:
		/**
		 * Using command mode with default speed.
		 * This method require to enable command mode before power on.
		 */
		/* Power off */
		BTH_PowerOff();

		/* Disable command mode */
		BTH_DisableCmd();

		/* Enable command mode */
		BTH_EnableCmd();

		/* Power on */
		BTH_PowerOn();
		break;
	default:
		/**
		 * Communication mode.
		 */
		/* Disable command mode */
		BTH_DisableCmd();

		/* Power on */
		BTH_PowerOn();
	}
}

void BTH_SetSpeed(cpu_data speed)
{

	gUartHandle.Instance			= USARTx;

	/* Deinit UART */
	HAL_UART_DeInit(&gUartHandle);

	gUartHandle.Init.BaudRate		= speed;
	gUartHandle.Init.WordLength		= UART_WORDLENGTH_8B;
	gUartHandle.Init.StopBits		= UART_STOPBITS_1;
	gUartHandle.Init.Parity			= UART_PARITY_NONE;
	gUartHandle.Init.Mode			= UART_MODE_TX_RX;
	gUartHandle.Init.HwFlowCtl		= UART_HWCONTROL_NONE;
	gUartHandle.Init.OverSampling	= UART_OVERSAMPLING_16;

	/* Initial UART */
	HAL_UART_Init(&gUartHandle);
}

void BTH_HardReset(void)
{
	/* Enter command mode with default speed */
	BTH_SetMode(BTH_Mode_Cmd_Default);

	/* Speed UART speed to default command speed */
	BTH_SetSpeed(BTH_DEFAULT_CMD_SPEED);

	/* Test */
	BTH_Write("AT\r\n");
	BTH_Read();

	/* Reset bluetooth to default */
	BTH_SetNameCmd(BTH_DEFAULT_NAME);
	BTH_SetSpeedCmd(BTH_DEFAULT_COMM_SPEED);
	BTH_SetPasswordCmd(BTH_DEFAULT_PWD);

	/* Disable command mode */
	BTH_DisableCmd();

	/* Speed UART speed to default communication speed */
	BTH_SetSpeed(BTH_DEFAULT_COMM_SPEED);

	/* Restart device */
	BTH_PowerOff();
	BTH_PowerOn();
}

bool BTH_SetNameCmd(const char *name)
{
	BTH_Write("AT+NAME=%s\r\n", name);
	return BTH_WaitForResponse();
}

bool BTH_SetSpeedCmd(cpu_data speed)
{
	BTH_Write("AT+UART=%d,0,0\r\n", speed);
	return BTH_WaitForResponse();
}

bool BTH_SetPasswordCmd(const char *password)
{
	BTH_Write("AT+PSWD=%s\r\n", password);
	return BTH_WaitForResponse();
}

const char *
BTH_GetVersion(void)
{
	const char *ret;

	BTH_Write("AT+VERSION?\r\n");
	ret = BTH_Read();

	return ret;
}

void
BTH_Write(const char *format,...)
{
	va_list args;

	va_start(args, format);
	vsnprintf (gTxBuffer, sizeof(gTxBuffer), format, args);
	va_end(args);

	gUARTReady = RESET;

	ptrRxBuffer = gRxBuffer;
	__HAL_UART_FLUSH_DRREGISTER(&gUartHandle);
	HAL_UART_Receive_DMA(&gUartHandle, (uint8_t *)ptrRxBuffer, 1);

	gUartHandle.State = HAL_UART_STATE_READY;
	if(HAL_UART_Transmit(&gUartHandle, (uint8_t *)gTxBuffer, strlen(gTxBuffer), HAL_UART_STATE_TIMEOUT) != HAL_OK)
	{
		trace_puts("Transmit error!");
	}

	trace_printf("Transmitted: %s", gTxBuffer);
}

const char *
BTH_Read(void)
{
	/*gUARTReady = RESET;

	ptrRxBuffer = gRxBuffer;
	__HAL_UART_FLUSH_DRREGISTER(&gUartHandle);
	HAL_UART_Receive_DMA(&gUartHandle, (uint8_t *)ptrRxBuffer, 1);*/

	cpu_data ticks = HAL_GetTick();
	ticks += 1000;

	while(gUARTReady == RESET && HAL_GetTick() < ticks);

	if(ticks <= HAL_GetTick())
		trace_puts("Timeout!\n");
	else
		trace_printf("Received: %s\n", gRxBuffer);

	return gRxBuffer;
}

/**
 * UART HAL Implementation
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
HAL_UART_MspInit(UART_HandleTypeDef *hsuart)
{
	  GPIO_InitTypeDef  GPIO_InitStruct;

		(void)&hsuart;	/* Prevent compiler warning. */

	  /*##-1- Enable peripherals and GPIO Clocks #################################*/
	  /* Enable GPIO TX/RX clock */
	  USARTx_TX_GPIO_CLK_ENABLE();
	  USARTx_RX_GPIO_CLK_ENABLE();

	  /* Enable UART clock */
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
	  /* NVIC for UART */
	  HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
	  HAL_NVIC_EnableIRQ(USARTx_IRQn);

		/* Initial DMA */
		gDMAHandle.Instance 		= DMA2_Stream2;
		gDMAHandle.Init.Channel		= DMA_CHANNEL_4;
		gDMAHandle.Init.Direction	= DMA_PERIPH_TO_MEMORY;
		gDMAHandle.Init.PeriphInc	= DMA_PINC_DISABLE;
		gDMAHandle.Init.MemInc 		= DMA_MINC_DISABLE;
		gDMAHandle.Init.PeriphDataAlignment 	= DMA_PDATAALIGN_BYTE;
		gDMAHandle.Init.Mode 		= DMA_CIRCULAR;
		gDMAHandle.Init.Priority 	= DMA_PRIORITY_HIGH;
		gDMAHandle.Init.FIFOMode	= DMA_FIFOMODE_DISABLE;
		gDMAHandle.Init.MemBurst	= DMA_MBURST_SINGLE;
		gDMAHandle.Init.PeriphBurst	= DMA_PBURST_SINGLE;
		HAL_DMA_Init(&gDMAHandle);

	  __DMA2_CLK_ENABLE();

	  __HAL_LINKDMA(&gUartHandle, hdmarx, gDMAHandle);

	  HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	  HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

	  trace_puts("HAL_UART_MspInit");
}

/**
  * @brief UART MSP De-Initialization
  *        This function frees the hardware resources used in this example:
  *          - Disable the Peripheral's clock
  *          - Revert GPIO and NVIC configuration to their default state
  * @param huart: UART handle pointer
  * @retval None
  */
void HAL_UART_MspDeInit(UART_HandleTypeDef *hsuart)
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

  HAL_DMA_DeInit(&gDMAHandle);
  HAL_NVIC_DisableIRQ(DMA2_Stream2_IRQn);

	trace_puts("HAL_UART_MspDeInit");
}

void
ISR_USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&gUartHandle);
}

void
ISR_DMA2_Stream2_IRQHandler(void)
{
    HAL_NVIC_ClearPendingIRQ(DMA2_Stream2_IRQn);
    HAL_DMA_IRQHandler(&gDMAHandle);
}

/* Callback if error has occured in the serial */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	(void)&huart;
	trace_puts("\r\n[ERROR] Serial error");
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	(void)&huart;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	(void)&huart;
	__HAL_UART_FLUSH_DRREGISTER(&gUartHandle);

	trace_putchar(*ptrRxBuffer);

    if (*ptrRxBuffer == 8 || *ptrRxBuffer == 127) // If Backspace or del
    {
    	ptrRxBuffer--;
        if (ptrRxBuffer < gRxBuffer) ptrRxBuffer = gRxBuffer;
    }
    else if (*ptrRxBuffer == '\n') // If Enter
    {
    	*++ptrRxBuffer = 0;
    	gUARTReady = SET;
    }
    else
    {
        if (++ptrRxBuffer > &gRxBuffer[RXBUFFERSIZE - 1]) // User typing too much, we can't have commands that big
        {
        	ptrRxBuffer = gRxBuffer;
        }
    }
}
