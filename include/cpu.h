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


 /**
  * @brief  Structure type to access the System Control Block (SCB).
  */
 typedef struct
 {
	 cpu_reg CPUID;                   /*!< Offset: 0x000 (R/ )  CPUID Base Register                                   */
	 cpu_reg ICSR;                    /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register                  */
	 cpu_reg VTOR;                    /*!< Offset: 0x008 (R/W)  Vector Table Offset Register                          */
	 cpu_reg AIRCR;                   /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register      */
	 cpu_reg SCR;                     /*!< Offset: 0x010 (R/W)  System Control Register                               */
	 cpu_reg CCR;                     /*!< Offset: 0x014 (R/W)  Configuration Control Register                        */
	 cpu_reg08  SHP[12];                 /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	 cpu_reg SHCSR;                   /*!< Offset: 0x024 (R/W)  System Handler Control and State Register             */
	 cpu_reg CFSR;                    /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register                    */
	 cpu_reg HFSR;                    /*!< Offset: 0x02C (R/W)  HardFault Status Register                             */
	 cpu_reg DFSR;                    /*!< Offset: 0x030 (R/W)  Debug Fault Status Register                           */
	 cpu_reg MMFAR;                   /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register                      */
	 cpu_reg BFAR;                    /*!< Offset: 0x038 (R/W)  BusFault Address Register                             */
	 cpu_reg AFSR;                    /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register                       */
	 cpu_reg PFR[2];                  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
	 cpu_reg DFR;                     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
	 cpu_reg ADR;                     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
	 cpu_reg MMFR[4];                 /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
	 cpu_reg ISAR[5];                 /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
	 cpu_reg RESERVED0[5];
	 cpu_reg CPACR;                   /*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register                   */
 } SCB_Type;

 /**
   * @brief Reset and Clock Control
   */

 typedef struct
 {
	 cpu_reg CR;            /*!< RCC clock control register,                                  Address offset: 0x00 */
	 cpu_reg PLLCFGR;       /*!< RCC PLL configuration register,                              Address offset: 0x04 */
	 cpu_reg CFGR;          /*!< RCC clock configuration register,                            Address offset: 0x08 */
	 cpu_reg CIR;           /*!< RCC clock interrupt register,                                Address offset: 0x0C */
	 cpu_reg AHB1RSTR;      /*!< RCC AHB1 peripheral reset register,                          Address offset: 0x10 */
	 cpu_reg AHB2RSTR;      /*!< RCC AHB2 peripheral reset register,                          Address offset: 0x14 */
	 cpu_reg AHB3RSTR;      /*!< RCC AHB3 peripheral reset register,                          Address offset: 0x18 */
	 cpu_reg RESERVED0;     /*!< Reserved, 0x1C                                                                    */
	 cpu_reg APB1RSTR;      /*!< RCC APB1 peripheral reset register,                          Address offset: 0x20 */
	 cpu_reg APB2RSTR;      /*!< RCC APB2 peripheral reset register,                          Address offset: 0x24 */
	 cpu_reg RESERVED1[2];  /*!< Reserved, 0x28-0x2C                                                               */
	 cpu_reg AHB1ENR;       /*!< RCC AHB1 peripheral clock register,                          Address offset: 0x30 */
	 cpu_reg AHB2ENR;       /*!< RCC AHB2 peripheral clock register,                          Address offset: 0x34 */
	 cpu_reg AHB3ENR;       /*!< RCC AHB3 peripheral clock register,                          Address offset: 0x38 */
	 cpu_reg RESERVED2;     /*!< Reserved, 0x3C                                                                    */
	 cpu_reg APB1ENR;       /*!< RCC APB1 peripheral clock enable register,                   Address offset: 0x40 */
	 cpu_reg APB2ENR;       /*!< RCC APB2 peripheral clock enable register,                   Address offset: 0x44 */
	 cpu_reg RESERVED3[2];  /*!< Reserved, 0x48-0x4C                                                               */
	 cpu_reg AHB1LPENR;     /*!< RCC AHB1 peripheral clock enable in low power mode register, Address offset: 0x50 */
	 cpu_reg AHB2LPENR;     /*!< RCC AHB2 peripheral clock enable in low power mode register, Address offset: 0x54 */
	 cpu_reg AHB3LPENR;     /*!< RCC AHB3 peripheral clock enable in low power mode register, Address offset: 0x58 */
	 cpu_reg RESERVED4;     /*!< Reserved, 0x5C                                                                    */
	 cpu_reg APB1LPENR;     /*!< RCC APB1 peripheral clock enable in low power mode register, Address offset: 0x60 */
	 cpu_reg APB2LPENR;     /*!< RCC APB2 peripheral clock enable in low power mode register, Address offset: 0x64 */
	 cpu_reg RESERVED5[2];  /*!< Reserved, 0x68-0x6C                                                               */
	 cpu_reg BDCR;          /*!< RCC Backup domain control register,                          Address offset: 0x70 */
	 cpu_reg CSR;           /*!< RCC clock control & status register,                         Address offset: 0x74 */
	 cpu_reg RESERVED6[2];  /*!< Reserved, 0x78-0x7C                                                               */
	 cpu_reg SSCGR;         /*!< RCC spread spectrum clock generation register,               Address offset: 0x80 */
	 cpu_reg PLLI2SCFGR;    /*!< RCC PLLI2S configuration register,                           Address offset: 0x84 */

 } RCC_TypeDef;

 /**
   * @brief FLASH Registers
   */

 typedef struct
 {
	 cpu_reg ACR;      /*!< FLASH access control register,   Address offset: 0x00 */
	 cpu_reg KEYR;     /*!< FLASH key register,              Address offset: 0x04 */
	 cpu_reg OPTKEYR;  /*!< FLASH option key register,       Address offset: 0x08 */
	 cpu_reg SR;       /*!< FLASH status register,           Address offset: 0x0C */
	 cpu_reg CR;       /*!< FLASH control register,          Address offset: 0x10 */
	 cpu_reg OPTCR;    /*!< FLASH option control register ,  Address offset: 0x14 */
	 cpu_reg OPTCR1;   /*!< FLASH option control register 1, Address offset: 0x18 */
 } FLASH_TypeDef;

 /* Memory mapping of Cortex-M4 Hardware */
 #define SCS_BASE            (0xE000E000UL)                            /*!< System Control Space Base Address  */
 #define SysTick_BASE        (SCS_BASE +  0x0010UL)                    /*!< SysTick Base Address               */
 #define NVIC_BASE           (SCS_BASE +  0x0100UL)                    /*!< NVIC Base Address                  */
 #define SCB_BASE            (SCS_BASE +  0x0D00UL)                    /*!< System Control Block Base Address  */

 #define SCB                 ((SCB_Type       *)     SCB_BASE      )   /*!< SCB configuration struct           */
 #define SysTick             ((SysTick_Type   *)     SysTick_BASE  )   /*!< SysTick configuration struct       */
 #define NVIC                ((NVIC_Type      *)     NVIC_BASE     )   /*!< NVIC configuration struct          */

 /**
   * @brief Peripheral_memory_map
   */
 #define FLASH_BASE            ((cpu_data)0x08000000) /*!< FLASH(up to 1 MB) base address in the alias region                         */
 #define CCMDATARAM_BASE       ((cpu_data)0x10000000) /*!< CCM(core coupled memory) data RAM(64 KB) base address in the alias region  */
 #define SRAM1_BASE            ((cpu_data)0x20000000) /*!< SRAM1(112 KB) base address in the alias region                             */
 #define SRAM2_BASE            ((cpu_data)0x2001C000) /*!< SRAM2(16 KB) base address in the alias region                              */
 #define SRAM3_BASE            ((cpu_data)0x20020000) /*!< SRAM3(64 KB) base address in the alias region                              */
 #define PERIPH_BASE           ((cpu_data)0x40000000) /*!< Peripheral base address in the alias region                                */
 #define BKPSRAM_BASE          ((cpu_data)0x40024000) /*!< Backup SRAM(4 KB) base address in the alias region                         */


 /* Legacy defines */
 #define SRAM_BASE             SRAM1_BASE
 #define SRAM_BB_BASE          SRAM1_BB_BASE


 /*!< Peripheral memory map */
 #define APB1PERIPH_BASE       PERIPH_BASE
 #define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
 #define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
 #define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000)

 #define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)
 #define FLASH_R_BASE          (AHB1PERIPH_BASE + 0x3C00)

 #define RCC                 ((RCC_TypeDef *) RCC_BASE)
 #define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)


#define ISR_VECTOR_TABLE_EN		1U
 /*
  * ************************************************************************************************
  * CPU Functions
  * ************************************************************************************************
  */
 void
 CPU_SystemReset(void);

 void
 CPU_ClockInit(void);

 void
 CPU_Reset(void);

#ifdef __cplusplus
}
#endif

#endif /* CPU_H_ */
