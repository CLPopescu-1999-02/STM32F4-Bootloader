/**
 * @file	cpu.c
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 23, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#include "cpu.h"
#include "hal/hal.h"

 /**
  * @brief	Initial CPU early.
  * 		This function is called after reset and before initial data section.
  *
  * @note	Usually set CPU to highest frequency for fastest data initialization.
  */
 void
 CPU_InitEarly(void)
 {
	  // Set clock to highest frequency and have the rest of the initializations run faster.
	  HAL_RCC_DeInitSystem();

	  HAL_RCC_InitSystem();
 }

 /**
  * @brief	Initial CPU.
  * 		This function is called after initial data section.
  */
 void
 CPU_Init(void)
 {
	 /* Update System Core Clock variable according to Clock Register Values */
	 HAL_RCC_Update();
 }

