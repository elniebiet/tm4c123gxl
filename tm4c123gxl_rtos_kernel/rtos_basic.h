#ifndef RTOS_BASIC_H
#define RTOS_BASIC_H

#include <stdint.h>

/* Thread Control Block (TCB) */
typedef struct {
	void *sp;
	
	/* other attribs */
	
} os_thread;

typedef void (*os_thread_handler)();

void os_init(void);
void os_thread_start(os_thread* thread, os_thread_handler thread_handler,
					void* stack_mem_loc, uint32_t stack_mem_size);
void os_scheduler(void);
void os_run(void);
void os_onstartup(void);						
											
#endif	//RTOS_BASIC_H
