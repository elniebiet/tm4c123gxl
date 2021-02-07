#ifndef MIROS_H
#define MIROS_H
#include <stdint.h>
/*Thread Control Block (TCB)*/
struct OSThread {
	void *sp; /*stack pointer*/
	/*other attributes associated with a thread*/
};
typedef struct OSThread OSThread; 

typedef void* (OSThreadHandler)();

void OS_init(void);

/*this function must be called when interrupts are disabled*/
void OS_sched(void); //to determine which thread to schedule next i.e triggering of context switch

/*fabricate register context for a thread stack*/
void OSThread_start(
	OSThread *me, //pointer to OSThread_start
	OSThreadHandler threadHandler, 
	void* stkSto, //pointer to stack memory 
	uint32_t stkSize //stack size 
);
	
#endif /*MIROS_H*/
