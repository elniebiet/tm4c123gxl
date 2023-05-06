#include <stdint.h>
#include "bsp.h"

/* background code: sequential with blocking version */

uint32_t stack_blinky1[40];
uint32_t* sp_blinky1 = &stack_blinky1[40];
void mainBlinky1(void){
	while (1) {
		BSP_ledGreenOn();
		BSP_delay(BSP_TICKS_PER_SEC / 4U);
		BSP_ledGreenOff();
		BSP_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}

uint32_t stack_blinky2[40];
uint32_t* sp_blinky2 = &stack_blinky2[40];
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
	
	/*Fabricate Cortex-M ISR stack frame for blinky1*/
	*(--sp_blinky1) = (1u << 24); // Program Status Register: sets bit 24 i.e THUMB state
	*(--sp_blinky1) = (uint32_t)&mainBlinky1; //set PC
	*(--sp_blinky1) = 0x0000000Eu; //set LR
	*(--sp_blinky1) = 0x0000000Cu; //set R12
	*(--sp_blinky1) = 0x00000003u; //set R3
	*(--sp_blinky1) = 0x00000002u; //set R2
	*(--sp_blinky1) = 0x00000001u; //set R1
	*(--sp_blinky1) = 0x00000000u; //set R0
	
	/*Fabricate Cortex-M ISR stack frame for blinky2*/
	*(--sp_blinky2) = (1u << 24); // Program Status Register: sets bit 24 i.e THUMB state
	*(--sp_blinky2) = (uint32_t)&mainBlinky2; //set PC
	*(--sp_blinky2) = 0x0000000Eu; //set LR
	*(--sp_blinky2) = 0x0000000Cu; //set R12
	*(--sp_blinky2) = 0x00000003u; //set R3
	*(--sp_blinky2) = 0x00000002u; //set R2
	*(--sp_blinky2) = 0x00000001u; //set R1
	*(--sp_blinky2) = 0x00000000u; //set R0
	
	while(1){
		;
	}
	
	
	//return 0;
}

