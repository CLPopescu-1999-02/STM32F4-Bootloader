/**
 ******************************************************************************
 * @file	stm32f4xx_macro.h
 * @author	Eakkasit L.
 * @version	V1.0.0
 * @date	24-Aug-2015
 * @brief	Brief of file description
 ******************************************************************************
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32F4XX_MACRO_H_
#define STM32F4XX_MACRO_H_

/* Includes ------------------------------------------------------------------*/
#include "cpu.h"

#ifdef __cplusplus
 extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
#define CPU_INL_FUNC	__attribute__((always_inline)) static inline

/* Exported functions --------------------------------------------------------*/

 /**
  * @brief	Disable IRQ Interrupts
  * 		This function disables IRQ interrupts by setting the I-bit in the CPSR.
  * 		Can only be executed in Privileged modes.
  */
 CPU_INL_FUNC
 void CPU_DisableIRQ(void)
 {
	 __asm volatile ("CPSID I");
 }

 /**
  * @brief	Enable IRQ Interrupts.
  * 		This function enables IRQ interrupts by clearing the I-bit in the CPSR.
  * 		Can only be executed in Privileged modes.
  */
 CPU_INL_FUNC
 void CPU_EnableIRQ(void)
 {
	 __asm volatile ("CPSIE I");
 }

 /**
  * @brief	Wait for interrupt.
  */
 CPU_INL_FUNC
 void CPU_WFI(void)
 {
	 __asm volatile ("WFI");
 }

 /**
  * @brief	Wait for event.
  */
 CPU_INL_FUNC
 void CPU_WFE(void)
 {
	 __asm volatile ("WFE");
 }

 /**
  * @brief	Send Event.
  */
 CPU_INL_FUNC
 void CPU_SEV(void)
 {
	 __asm volatile ("SEV");
 }

 /**
  * @brief	Instruction Synchronization Barrier.
  */
 CPU_INL_FUNC
 void CPU_ISB(void)
 {
	 __asm volatile ("DSB");
 }

 /**
  * @brief	Data Synchronization Barrier.
  */
 CPU_INL_FUNC
 void CPU_DSB(void)
 {
	 __asm volatile ("DSB");
 }

 /**
  * @brief	Data Memory Barrier.
  */
 CPU_INL_FUNC
 void CPU_DMB(void)
 {
	 __asm volatile ("DMB");
 }

 /**
  * @brief	Supervisor call.
  */
 CPU_INL_FUNC
 void CPU_SVC(void)
 {
	 __asm volatile ("SVC 0x01");
 }

 /**
  * @brief	Get Control Register.
  * 		This function returns the content of the Control Register.
  * @retval	Control Register value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetCONTROL(void)
 {
	 register cpu_data result;

	__asm volatile ("MRS %0, control" : "+r" (result) );

	return result;
 }

 /**
  * @brief	Set CONTROL register.
  * 		This function writes the given value to the Control Register.
  * @param [in]    control  Control Register value to set
  */
 CPU_INL_FUNC
 void void CPU_SetCONTROL(register cpu_data control)
 {
 	__asm volatile ("MSR control, %0" : : "r" (control) );
 }

 /**
  * @brief	Get Process Stack Pointer (PSP).
  * 		This function returns the current value of the Process Stack Pointer (PSP).
  * @retval	Return top of process stack pointer.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetPSP(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, psp"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Process Stack Pointer (PSP).
  * 		This function assigns the given value to the Process Stack Pointer (PSP).
  * @param [in]    topOfProcStack  Process Stack Pointer value to set
  */
 CPU_INL_FUNC
 void CPU_SetPSP(register cpu_data topOfProcStack)
 {
 	__asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get Process Stack Pointer (MSP).
  * 		This function returns the current value of the Main Stack Pointer (MSP).
  *
  * @retval	MSP Register value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetMSP(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, msp"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Process Stack Pointer (MSP).
  * 		This function assigns the given value to the Main Stack Pointer (MSP).
  * @param [in]    topOfProcStack  Main Stack Pointer value to set
  */
 CPU_INL_FUNC
 void CPU_SetMSP(register cpu_data topOfProcStack)
 {
 	__asm volatile ("MSR msp, %0" : : "r" (topOfProcStack) );
 }

 /**
  * @brief	Get IPSR Register.
  * 		This function returns the content of the IPSR Register.
  *
  * @retval	IPSR Register value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetIPSR(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, ipsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get APSR Register.
  * 		This function returns the content of the APSR Register.
  *
  * @retval	APSR Register value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetAPSR(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, apsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get xPSR Register.
  * 		This function returns the content of the xPSR Register.
  *
  * @retval	xPSR Register value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetxPSR(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, xpsr"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Get Priority Mask (PRIMASK).
  * 		This function returns the current state of the priority mask bit from the Priority Mask Register (PRIMASK).
  *
  * @retval	Priority Mask value.
  */
 CPU_INL_FUNC
 cpu_data CPU_GetPRIMASK(void)
 {
	  register cpu_data result;

	  __asm volatile ("MRS %0, primask"  : "=r" (result) );

	  return(result);
 }

 /**
  * @brief	Set Priority Mask Register (PRIMASK).
  * 		This function assigns the given value to the Priority Mask Register (PRIMASK).
  *
  * @param [in]    priMask  Priority Mask value
  */
 CPU_INL_FUNC
 void CPU_SetPRIMASK(register cpu_data priMask)
 {
 	__asm volatile ("MSR primask, %0" : : "r" (priMask) );
 }

#ifdef __cplusplus
}
#endif

#endif /* STM32F4XX_MACRO_H_ */

/*****************************END OF FILE**************************************/
