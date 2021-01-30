#include <stdint.h>
#define __FPU_PRESENT  1  /*!< FPU present or not                                                    */
//#include "tm4c_cmsis.h"
#include "delay.h"
#include "bsp.h"
#include "intrinsics.h"
#include "tm4c123gh6pm.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

#define SYS_CLOCK_HZ 16000000u

int main() {
    
    SYSCTL->RCGCGPIO  |= (1U << 5); /* enable Run mode for GPIOF */
    SYSCTL->GPIOHBCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_AHB->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_AHB->DEN |= (LED_RED | LED_BLUE | LED_GREEN);

    SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U; //half a sec interrupt
    SysTick->VAL  = 0U; //clear on write register
    SysTick->CTRL = (1U << 2) | (1U << 1) | 1U; //set bits 2, 1, 0 for clock source, interrupt enable and counter enable respectively

    SysTick_Handler();

    __enable_interrupt(); //clear primask bit
    while (1) {
        GPIOF_AHB->DATA_Bits[LED_GREEN] = LED_GREEN;
        GPIOF_AHB->DATA_Bits[LED_GREEN] = 0U;
    }
    //return 0;
}
