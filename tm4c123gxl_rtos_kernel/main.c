#include <stdint.h>
#include "bsp.h"
#include "rtos_basic.h"

uint32_t thread1_stack[40];
os_thread thread1;
uint32_t thread2_stack[40];
os_thread thread2;
uint32_t thread3_stack[40];
os_thread thread3;

void thread1_main(void){
	while (1) {
		bsp_led_green_on();
		bsp_delay(BSP_TICKS_PER_SEC / 4U);
		bsp_led_green_off();
		bsp_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}

void thread2_main(void){
	while (1) {
		bsp_led_blue_on();
		bsp_delay(BSP_TICKS_PER_SEC / 2U);
		bsp_led_blue_off();
		bsp_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}

void thread3_main(void){
	while (1) {
		bsp_led_red_on();
		bsp_delay(BSP_TICKS_PER_SEC / 2U);
		bsp_led_red_off();
		bsp_delay(BSP_TICKS_PER_SEC * 3U / 4U);
	}
}

int main() {
	bsp_init();
	os_init();
	
	/* fabricate tm4c123 ISR stack frame for threads */
	os_thread_start(&thread1, &thread1_main, &thread1_stack[0], sizeof(thread1_stack));
	os_thread_start(&thread2, &thread2_main, &thread2_stack[0], sizeof(thread2_stack));
	os_thread_start(&thread3, &thread3_main, &thread3_stack[0], sizeof(thread3_stack));
	
	/* transfer control to rtos */
	os_run();
	
	
	//return 0;
}

