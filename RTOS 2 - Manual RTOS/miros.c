#include "miros.h"
#include <stdint.h>

OSThread* volatile OS_curr; //pointer to get current thread 
OSThread* volatile OS_next; //pointer to get next thread

void OS_init(void){
	//set PendSV interrupt priority to the lowest level
	*(uint32_t* volatile)0xE000ED20 |= (0xFFu << 16);
}

void OS_sched(void){
	/*OS_next = ... */ 
	if(OS_next != OS_curr){
		*(uint32_t volatile *)0xE000ED04 = (1u << 28);
	}
}
void OSThread_start(
	OSThread *me, //pointer to OSThread_start
	OSThreadHandler threadHandler, 
	void* stkSto, //pointer to stack memory 
	uint32_t stkSize //stack size 
){
	
	/* round down the stack from top to the 8-byte boundary, 
	 * NOTE: ARM Cortex-M stack grows down from hi -> low memory
	 */
	uint32_t* sp = (uint32_t*)((((uint32_t)stkSto + stkSize) / 8) * 8);
	uint32_t* stk_limit;
	*(--sp) = (1U << 24);  /* xPSR */
	*(--sp) = (uint32_t)threadHandler; /* PC */
	*(--sp) = 0x0000000EU; /* LR  */
	*(--sp) = 0x0000000CU; /* R12 */
	*(--sp) = 0x00000003U; /* R3  */
	*(--sp) = 0x00000002U; /* R2  */
	*(--sp) = 0x00000001U; /* R1  */
	*(--sp) = 0x00000000U; /* R0  */
	/* additionally, fake registers R4-R11 */
	*(--sp) = 0x0000000BU; /* R11 */
	*(--sp) = 0x0000000AU; /* R10 */
	*(--sp) = 0x00000009U; /* R9 */
	*(--sp) = 0x00000008U; /* R8 */
	*(--sp) = 0x00000007U; /* R7 */
	*(--sp) = 0x00000006U; /* R6 */
	*(--sp) = 0x00000005U; /* R5 */
	*(--sp) = 0x00000004U; /* R4 */
	
	/* save the top of the stack in the thread's attribute*/
	me->sp = sp; 
	
	/*round up the bottom of the stack to the 8-byte boundary*/
	stk_limit = (uint32_t*)(((((uint32_t)stkSto - 1u) / 8) + 1u) * 8);
	
	/*pre fill unused part of stack with 0xDEADBEEF*/
	for(sp = sp - 1u; sp >= stk_limit; --sp){
		*sp = 0xDEADBEEFu;
	}
}

__asm
void PendSV_Handler(){
	IMPORT OS_curr //extern variable
	IMPORT OS_next //extern variable

	/*	disable interrupt */
//__disable_irq(); 
	CPSID         I

	//  if(OS_curr != (OSThread*)0){ 
	LDR           r1,=OS_curr   //@0x00000680
	LDR           r1,[r1,#0x00]
	CBZ           r1,PendSV_restore

	/*  push registers r4-r11 on the stack */       
	PUSH					{r4-r11}
	LDR           r1,=OS_curr   //@0x00000680
	LDR           r1,[r1,#0x00]

	//  OS_curr->sp = sp; 
	STR           sp,[r1,#0x00]

	//             } 

	/* restore context of next thread */
PendSV_restore		
//             sp = OS_next->sp; 
	LDR           r1,=OS_next   //@0x00000684
	LDR           r1,[r1,#0x00]
	LDR           sp,[r1,#0x00]
	
//             OS_curr = OS_next; 
	LDR           r1,=OS_next   //@0x00000684
	LDR           r1,[r1,#0x00]
	LDR           r2,=OS_curr   //; @0x00000680
	STR           r1,[r2,#0x00]
	
	/* pop registers r4-r11 */ 
	POP						{r4-r11}
	
	/*enable interrupt*/
//             __enable_irq(); 
	CPSIE         I
	BX						lr
	//     } 
}

