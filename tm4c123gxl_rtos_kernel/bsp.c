/* Board Support Package (BSP) for the EK-TM4C123GXL board */
#include <stdint.h>  /* Standard integers. WG14/N843 C99 Standard */

#include "bsp.h"

//#include "TM4C123.h"                    // Device header
//#include "TM4C123GH6PM.h" /* the TM4C MCU Peripheral Access Layer (TI) */
#include "TM4C123_CMSIS.h"
#include "rtos_basic.h"

/* on-board LEDs */
#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

static uint32_t volatile l_tickCtr;

void SysTick_Handler(void) 
{
    ++l_tickCtr;
	
	__disable_irq();
	os_scheduler();
	__enable_irq();
}

void os_onstartup(void)
{
	SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / BSP_TICKS_PER_SEC);

	/* set systick intr priority to highest */
	NVIC_SetPriority(SysTick_IRQn, 0u);
}

void bsp_init(void) 
{
    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
}

uint32_t bsp_tick_ctr(void) 
{
    uint32_t tickCtr;

    __disable_irq();
    tickCtr = l_tickCtr;
    __enable_irq();

    return tickCtr;
}

void bsp_delay(uint32_t ticks) 
{
    uint32_t start = bsp_tick_ctr();
    while ((bsp_tick_ctr() - start) < ticks) {
    }
}

void bsp_led_red_on(void)
{
    GPIOF_AHB->DATA_Bits[LED_RED] = LED_RED;
}

void bsp_led_red_off(void) 
{
    GPIOF_AHB->DATA_Bits[LED_RED] = 0U;
}

void bsp_led_blue_on(void) 
{
    GPIOF_AHB->DATA_Bits[LED_BLUE] = LED_BLUE;
}

void bsp_led_blue_off(void)
{
    GPIOF_AHB->DATA_Bits[LED_BLUE] = 0U;
}

void bsp_led_green_on(void) 
{
    GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
}

void bsp_led_green_off(void) 
{
    GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
}


void Q_onAssert(char const *module, int loc) 
{
    /* TBD: damage control */
    (void)module; /* avoid the "unused parameter" compiler warning */
    (void)loc;    /* avoid the "unused parameter" compiler warning */
    NVIC_SystemReset();
}
