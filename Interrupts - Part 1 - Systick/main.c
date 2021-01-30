#include <stdint.h>
#define __FPU_PRESENT  1  /*!< FPU present or not                                                    */
#include "tm4c_cmsis.h"
#include "delay.h"
#include "bsp.h"
#include "intrinsics.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

#define SYS_CLOCK_HZ 16000000u

int main() {
  
    SYSCTL->RCGC2 |= (1U << 5);  /* enable clock for GPIOF */
    SYSCTL->GPIOHSCTL |= (1U << 5); /* enable AHB for GPIOF */
    GPIOF_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
    GPIOF_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
    
    SysTick->LOAD = SYS_CLOCK_HZ/2u - 1u; //half a sec interrupt
    SysTick->VAL = 0u; //clear on write register
    SysTick->CTRL = (1u << 2) | (1u << 1) | 1u; //set bits 2, 1, 0 for clock source, interrupt enable and counter enable respectively
    
    __enable_interrupt(); //clear primask bit
    
//    GPIOF_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
    while (1) {
        ;
    }
    
    //return 0;
}
