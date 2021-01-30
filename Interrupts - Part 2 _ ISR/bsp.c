/* Board Support Package */
#define __FPU_PRESENT  1  /*!< FPU present or not                                                    */
#include "tm4c_cmsis.h"
#include "bsp.h"

__stackless void assert_failed(const char* file, int line){
	/* TBD: damage control */
	NVIC_SystemReset(); //reset the system //NVIC function
}
//test the weak aliasing: by creating a custom systic_handler

void SysTick_Handler(void){
  GPIOF_HS->DATA_Bits[LED_RED] ^= LED_RED;
}