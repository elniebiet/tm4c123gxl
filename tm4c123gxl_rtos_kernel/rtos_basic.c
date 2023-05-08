#include "rtos_basic.h"

/**
* basic rtos implementation for tm4c123 cortex-m mcu
*/

os_thread* volatile curr_thread;
os_thread* volatile next_thread;

void os_init(void)
{
	/**
	* set pendsv interrupt priority to lowest in SysPri3 reg
	*/
	*(uint32_t volatile *)0xe000ed20 |= (0xffu << 16);
}
void os_thread_start(os_thread* thread, os_thread_handler thread_handler,
					void* stack_mem_loc, uint32_t stack_mem_size)
{
	/**
	 * tm4c123 stack grows downwards from high to low mem - so we start at top
	 * also round to 8-byte boundary
	*/
	uint32_t *sp = (uint32_t*)((((uint32_t)stack_mem_loc + stack_mem_size) / 8 ) * 8 );
	uint32_t *stack_limit;
	
	*(--sp) = (1u << 24); // Program Status Register: sets bit 24 i.e THUMB state
	*(--sp) = (uint32_t)thread_handler; //set PC
	*(--sp) = 0x0000000Eu; //LR
	*(--sp) = 0x0000000Cu; //R12
	*(--sp) = 0x00000003u; //R3
	*(--sp) = 0x00000002u; //R2
	*(--sp) = 0x00000001u; //R1
	*(--sp) = 0x00000000u; //R0
	/* additionally, temp registers R4-R11 */
    *(--sp) = 0x0000000BU; //R11
    *(--sp) = 0x0000000AU; //R10
    *(--sp) = 0x00000009U; //R9
    *(--sp) = 0x00000008U; //R8
    *(--sp) = 0x00000007U; //R7
    *(--sp) = 0x00000006U; //R6
    *(--sp) = 0x00000005U; //R5
    *(--sp) = 0x00000004U; //R4
	
	/* save top of stack */
	thread->sp = sp;
	
	/* round up bottom of stack to 8-byte boundary */
	stack_limit = (uint32_t*)(((((uint32_t)stack_mem_loc - 1u) / 8) + 1u) * 8 );
	
	/* pre-fill the unused part of the stack with 0xdeadbeef */
	for(sp = sp - 1u; sp >= stack_limit; --sp)
	{
		*sp = 0xdeadbeefu;
	}
}

void os_scheduler(void)
{
	/* call this func with interrupts disabled */
	if(curr_thread != next_thread)
	{
		/* trigger pendsv intr */
		*(uint32_t volatile*)0xe000ed04 |= (1u << 28);		
	}
}

/* inline assembly syntax for Compiler 6 (ARMCLANG) */
__attribute__ ((naked))
void PendSV_Handler(void) {
	/**
	* trigger pendsv handler in tm4c123 by setting SysCtrl reg (0xE000ED04) bit -> 0x10000000, 
	* before this handler is called, ensure to set pendsv intr priority to lowest so its is not preempted by other interrupts like systick
	*/
#if 0
	void* sp;
	__disable_irq();
	/* ensure we're not coming from reset */
	if(curr_thread != (os_thread*)0)
	{
		/*push regs r4-r11 onto curr stack */
		curr_thread->sp = sp;
	}
	sp = next_thread->sp;
	curr_thread = next_thread;
	/* pop regs r4-r11 from next */
	__enable_irq();
#endif //0
	__asm volatile (
		/* __disable_irq(); */
		"  CPSID         I                 \n"
		/* ensure we're not coming from reset */
		/* if(curr_thread != (os_thread*)0) {*/
		"  LDR           r1,=curr_thread       \n"
		"  LDR           r1,[r1,#0x00]     \n"
		"  CBZ           r1,PendSV_restore \n"

		/* push regs r4-r11 onto curr stack */ 
		"  PUSH          {r4-r11}          \n"

		/* curr_thread->sp = sp; */
		"  LDR           r1,=curr_thread       \n"
		"  LDR           r1,[r1,#0x00]     \n"
		"  STR           sp,[r1,#0x00]     \n"
		/* } */

	"PendSV_restore:                   \n"
		/* sp = next_thread->sp; */
		"  LDR           r1,=next_thread       \n"
		"  LDR           r1,[r1,#0x00]     \n"
		"  LDR           sp,[r1,#0x00]     \n"

		/* curr_thread = next_thread; */
		"  LDR           r1,=next_thread       \n"
		"  LDR           r1,[r1,#0x00]     \n"
		"  LDR           r2,=curr_thread       \n"
		"  STR           r1,[r2,#0x00]     \n"

		/* pop registers r4-r11 from next */
		"  POP           {r4-r11}          \n"
		/* __enable_irq(); */
		"  CPSIE         I                 \n"
		"  BX            lr                \n"
    );
}
