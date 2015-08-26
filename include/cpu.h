/**
 * @file	cpu.h
 * @brief	Framework header file.
 * @details	Framework header file.
 * @version	1.0
 * @date	Aug 23, 2015
 * @author	Eakkasit L.
 * @bug		No known bug
 * @warning	Improper use can crash your application
 * @copyright	GNU Public License.
 */

#ifndef CPU_H_
#define CPU_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

 /*
  * ************************************************************************************************
  * CPU Types
  * ************************************************************************************************
  */
 /**
  * @brief	General CPU types define.
  */
 typedef            void        cpu_void;
 typedef            char        cpu_char;                        /*  8-bit character                                     */
 typedef  unsigned  char        cpu_boolean;                     /*  8-bit boolean or logical                            */
 typedef  unsigned  char        cpu_uint08;                      /*  8-bit unsigned integer                              */
 typedef    signed  char        cpu_sint08;                      /*  8-bit   signed integer                              */
 typedef  unsigned  short       cpu_uint16;                      /* 16-bit unsigned integer                              */
 typedef    signed  short       cpu_sint16;                      /* 16-bit   signed integer                              */
 typedef  unsigned  int         cpu_uint32;                      /* 32-bit unsigned integer                              */
 typedef    signed  int         cpu_sint32;                      /* 32-bit   signed integer                              */
 typedef  unsigned  long  long  cpu_uint64;                      /* 64-bit unsigned integer                              */
 typedef    signed  long  long  cpu_sint64;                      /* 64-bit   signed integer                              */

 typedef            float       cpu_fp32;                        /* 32-bit floating point                                */
 typedef            double      cpu_fp64;                        /* 64-bit floating point                                */

 typedef  volatile  cpu_uint08  cpu_reg08;                       /*  8-bit register                                      */
 typedef  volatile  cpu_uint16  cpu_reg16;                       /* 16-bit register                                      */
 typedef  volatile  cpu_uint32  cpu_reg32;                       /* 32-bit register                                      */
 typedef  volatile  cpu_uint64  cpu_reg64;                       /* 64-bit register                                      */

 /**
  * @brief	Using 32 bit CPU register and data for STM32F4xx.
  */
 typedef			cpu_reg32	cpu_reg;
 typedef			cpu_uint32	cpu_data;
 typedef  volatile  cpu_uint32* cpu_addr;

#define ISR_VECTOR_TABLE_EN		1U
 /*
  * ************************************************************************************************
  * CPU Functions
  * ************************************************************************************************
  */

 /**
  * @brief	Initial CPU early.
  * 		This function is called after reset and before initial data section.
  *
  * @note	Usually set CPU to highest frequency for fastest data initialization.
  */
 void
 CPU_InitEarly(void);

 /**
  * @brief	Initial CPU.
  * 		This function is called after initial data section.
  */
 void
 CPU_Init(void);

 /**
  * @brief	Initial CPU Clock.
  */
 void
 CPU_ClockInit(void);

#ifdef __cplusplus
}
#endif

#endif /* CPU_H_ */
