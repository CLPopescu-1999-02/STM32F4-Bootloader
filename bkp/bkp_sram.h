/**
 ******************************************************************************
 * @file	bkp_sram.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BKP_SRAM_H_
#define BKP_SRAM_H_

/* Includes ------------------------------------------------------------------*/
#include "cpu.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

#define	BKP_SRAM_BASE		BKPSRAM_BASE			/* Backup SRAM base address in the alias region */
#define	BKP_SRAM_SIZE		((cpu_data)0x1000)		/* Backup SRAM Size (4 KB) */

/* Exported macro ------------------------------------------------------------*/
#define	BKP_SRAM_Read08(addr)				(*(volatile cpu_uint08 *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_Write08(addr,value)		(*(volatile cpu_uint08 *) (BKP_SRAM_BASE + addr) = (value))
#define	BKP_SRAM_Read16(addr)				(*(volatile cpu_uint16 *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_Write16(addr,value)		(*(volatile cpu_uint16 *) (BKP_SRAM_BASE + addr) = (value))
#define	BKP_SRAM_Read32(addr)				(*(volatile cpu_uint32 *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_Write32(addr,value)		(*(volatile cpu_uint32 *) (BKP_SRAM_BASE + addr) = (value))
#define	BKP_SRAM_Read64(addr)				(*(volatile cpu_uint64 *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_Write64(addr,value)		(*(volatile cpu_uint64 *) (BKP_SRAM_BASE + addr) = (value))
#define	BKP_SRAM_ReadFp32(addr)				(*(volatile cpu_fp32   *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_WriteFp32(addr,value)		(*(volatile cpu_fp32   *) (BKP_SRAM_BASE + addr) = (value))
#define	BKP_SRAM_ReadFp64(addr)				(*(volatile cpu_fp64   *) (BKP_SRAM_BASE + addr))
#define	BKP_SRAM_WriteFp64(addr,value)		(*(volatile cpu_fp64   *) (BKP_SRAM_BASE + addr) = (value))

/* Exported functions --------------------------------------------------------*/
void
BKP_SRAM_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* BKP_SRAM_H_ */

/*****************************END OF FILE**************************************/
