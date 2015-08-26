/**
 ******************************************************************************
 * @file	bootloader.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BOOTLOADER_H_
#define BOOTLOADER_H_

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include "cpu.h"

#ifdef __cplusplus
 extern "C" {
#endif

 /* Exported constants --------------------------------------------------------*/

 #define	LD_FORCE_PORT						GPIOD
 #define	LD_FORCE_PIN						GPIO_PIN_13
 #define	LD_FORCE_CLK_EN						__GPIOD_CLK_ENABLE

 #define	LD_FIRMWARE_START_ADDR				((cpu_data)0x08020000)		/* Firmware space */
 #define	LD_FIRMWARE_MAX_COUNT				7							/* Max firmware count (using sector 5 - 11 (128KB for each sector)) */

 #define	LD_FIRMWARE_SP_MIN					((cpu_data)0x08020000)
 #define	LD_FIRMWARE_SP_MAX					((cpu_data)0x08020000)

/* Exported types ------------------------------------------------------------*/
typedef enum
{
	LD_START_CODE_LOADER	= 0x00000000,
	LD_START_CODE_FIRMWARE	= 0x00000001,
	LD_START_CODE_FLASH		= 0x00000002,
} LD_Startup_Code_t;

typedef struct
{
	cpu_uint08			id;
	cpu_data			addr;
	cpu_data			size;
	const char			*name;
} ld_firmware_t;

typedef struct
{
	cpu_data			signature;
	LD_Startup_Code_t	start_code;
	cpu_uint08			default_firmware_id;
	ld_firmware_t		firmwares[LD_FIRMWARE_MAX_COUNT];

	/* Bluetooth configurations */
	cpu_data			bth_speed;
}ld_bkp_sram_t;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
void
LD_Init(void);

bool
LD_IsForceStart(void);

void
LD_Start(void);

void
LD_JumpToFirmware(cpu_data addr);


extern volatile ld_bkp_sram_t *gBkpSram;

#ifdef __cplusplus
}
#endif

#endif /* BOOTLOADER_H_ */

/*****************************END OF FILE**************************************/
