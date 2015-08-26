/**
 ******************************************************************************
 * @file	bootloader.c
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

#include "bootloader.h"
#include "stm32f4xx_macro.h"
#include "bluetooth.h"
#include "diag/Trace.h"
#include "bkp_sram.h"

#define	LD_SIGNATURE	((cpu_data)0x12345676)

volatile ld_bkp_sram_t *gBkpSram = (volatile ld_bkp_sram_t *)BKP_SRAM_BASE;;

void
LD_JumpToFirmware(cpu_data addr);

void
LD_ProcessCmd(void);

void
LD_ProcessFlashFirmware(void);

void
LD_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;

	/* Initial Power pin */
	GPIO_InitStruct.Pin       = LD_FORCE_PIN;
	GPIO_InitStruct.Mode      = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull      = GPIO_PULLUP;
	GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
	HAL_GPIO_Init(LD_FORCE_PORT, &GPIO_InitStruct);
	LD_FORCE_CLK_EN();
}

bool
LD_IsForceStart(void)
{
	return (HAL_GPIO_ReadPin(LD_FORCE_PORT, LD_FORCE_PIN) == GPIO_PIN_RESET);
}

void
LD_Start(void)
{
	bool blIsForceStart = false;

	/* Check if force start to bootloader mode */
	blIsForceStart = LD_IsForceStart();

	/**
	 * Initial backup SRAM.
	 */
	BKP_SRAM_Init();

	/* Initial bluetooth module */
	BTH_Init();

	/**
	 * Check signature initialization (power lost).
	 * The SRAM is using to save non-critical configurations and reset on power lost.
	 */
#if 0
	if(gBkpSram->signature != LD_SIGNATURE)
#endif
	{
		/* Power lost, re-initialize */
		gBkpSram->signature = LD_SIGNATURE;

		/* initial bluetooth configuration */
		gBkpSram->bth_speed	= BTH_DEFAULT_COMM_SPEED;

		/**
		 * Hard reset bluetooth module.
		 * Bluetooth setting is not critical then reset it when power lost.
		 */
		BTH_HardReset();
	}

	if(blIsForceStart || gBkpSram->start_code != LD_START_CODE_FIRMWARE)
	{
		/* Check force start mode */
		if(blIsForceStart)
		{
			/* Process command from user for force start to boot loader */
			LD_ProcessCmd();
		}
		else if(gBkpSram->start_code == LD_START_CODE_FLASH)
		{
			/* Process firmware flashing */
			LD_ProcessFlashFirmware();
		}
	}

	/* Startup firmware */
	LD_JumpToFirmware(gBkpSram->firmwares[gBkpSram->default_firmware_id].addr);
}

void
LD_JumpToFirmware(cpu_data addr)
{
	/* Check firmware address */
	if(addr < LD_FIRMWARE_START_ADDR)
	{
		trace_printf("Invalid firmware address: 0x%X", addr);
		return;			/* return on try to start from reserved space */
	}

	/* Check main stack pointer */
	cpu_data sp = *((volatile cpu_data *)addr);
	if(sp < LD_FIRMWARE_SP_MIN || sp > LD_FIRMWARE_SP_MAX)
	{
		trace_printf("Invalid stack pointer: 0x%X", sp);
		return;
	}

	/* Set firmware Main Stack Pointer */
	CPU_SetMSP(sp);

	/**
	 * Jump to firmware address .
	 * Note:	-Skip 4 bytes for stack pointer.
	 * 			-Skip 1 byte for thumb mode.
	 */
	CPU_BX(addr + 4 + 1);

	/* Should not reach here, it should jump to firmware address. */
	trace_puts("Jump to firmware fail!");
	while(1);
}

void
LD_ProcessCmd(void)
{

}

void
LD_ProcessFlashFirmware(void)
{

}
