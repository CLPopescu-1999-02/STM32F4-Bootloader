/**
 * @file	main.c
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
#include "stm32f4xx_hal.h"
#include "diag/Trace.h"
#include "bluetooth.h"


#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

#define	BLINK_LED_ON(port,pin)	HAL_GPIO_WritePin(BLINK_GPIOx(port), BLINK_PIN_MASK(pin), GPIO_PIN_SET);

// Keep the LED on for 1/4 of a second.
#define ON_OFF_TICKS (TIMER_FREQUENCY_HZ * 1 / 4)

typedef enum
{
	LED3	= 13,
	LED4	= 12,
	LED5	= 14,
	LED6	= 15,
} leds;

#define TIMER_FREQUENCY_HZ (1000u)

typedef uint32_t timer_ticks_t;

volatile timer_ticks_t timer_delayCount;

void
blink_led_init()
{
  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= (1 << 3);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = (0xF << 12);
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(BLINK_GPIOx(3), &GPIO_InitStructure);
}

inline void
__attribute__((always_inline))
blink_led_on(leds led)
{
	HAL_GPIO_WritePin(BLINK_GPIOx(3), BLINK_PIN_MASK(led), GPIO_PIN_SET);
}

inline void
__attribute__((always_inline))
blink_led_off(leds led)
{
	HAL_GPIO_WritePin(BLINK_GPIOx(3), BLINK_PIN_MASK(led), GPIO_PIN_RESET);
}

void
timer_start (void)
{
  // Use SysTick as reference for the delay loops.
  SysTick_Config (SystemCoreClock / TIMER_FREQUENCY_HZ);
}

void
timer_sleep (timer_ticks_t ticks)
{
  timer_delayCount = ticks;

  // Busy wait until the SysTick decrements the counter to zero.
  while (timer_delayCount != 0u)
    ;
}

void
timer_tick (void)
{
  // Decrement to zero the counter used by the delay routine.
  if (timer_delayCount != 0u)
    {
      --timer_delayCount;
    }
}


void
ISR_SysTick_Handler (void)
{
  timer_tick ();
}

#define BT_EN_PIN	LED6

int
main(void)
{
	// Send a greeting to the trace device (skipped on Release).
	trace_puts("Hello ARM World!");

	// At this stage the system clock should have already been configured
	// at high speed.
	trace_printf("System clock: %uHz\n", SystemCoreClock);

	blink_led_init();
	blink_led_off(LED3);
	blink_led_off(LED4);
	blink_led_off(LED5);
	blink_led_off(LED6);

	BTH_Init();
	const char *msg;

	msg = BTH_GetVersion();
	if(msg != 0)
	{
		trace_printf("Bluetooth Name: %s\n", msg);
	}

	timer_start();

	while(1)
	{
		blink_led_on(LED3);
		timer_sleep(ON_OFF_TICKS);
		blink_led_off(LED3);
		timer_sleep(ON_OFF_TICKS);
	}

	return 0;
}

