#include <stdint.h>
#include "bsp.h"
#include "miros.h"

/* background code: sequential with blocking version */

uint32_t stack_blinky1[40];
OSThread blinky1;
void mainBlinky1(void){
	while (1) {
		BSP_ledGreenOn();
		BSP_delay(BSP_TICKS_PER_SEC / 4U);
		BSP_ledGreenOff();
		BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}

uint32_t stack_blinky2[40];
OSThread blinky2;
void mainBlinky2(void){
	while (1) {
		BSP_ledBlueOn();
		BSP_delay(BSP_TICKS_PER_SEC / 4U);
		BSP_ledBlueOff();
		BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}
int main() {
	BSP_init();
	
	OS_init(); 
	
	/*Fabricate Cortex-M ISR stack frame for blinky1*/
	OSThread_start( &blinky1, 
									&mainBlinky1, 
									stack_blinky1, 
									sizeof(stack_blinky1)
								);
	
	/*Fabricate Cortex-M ISR stack frame for blinky2*/
	OSThread_start( &blinky2, 
									&mainBlinky2, 
									stack_blinky2, 
									sizeof(stack_blinky2)
								);
	
	while(1){
		;
	}
	
	
	//return 0;
}

