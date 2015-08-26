/**
 ******************************************************************************
 * @file	time.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	25-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef TIME_H_
#define TIME_H_

/* Includes ------------------------------------------------------------------*/
#include "cpu.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
#define	TIME_SYSTICK_FREQ_HZ		1000

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

 void
 TIME_Init(void);

 cpu_data
 TIME_GetTicks(void);

 cpu_data
 TIME_GetMs(void);

 void
 TIME_Delay(cpu_data ticks);

 void
 TIME_DelayMs(cpu_data ms);

extern volatile cpu_data time_ticks;

#ifdef __cplusplus
}
#endif

#endif /* TIME_H_ */

/*****************************END OF FILE**************************************/
