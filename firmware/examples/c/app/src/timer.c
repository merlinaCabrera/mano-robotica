#include "timer.h"
#include "mef.h"
#include "sapi.h"

volatile uint8_t FLAG_T;


void myTickHook(void *ptr){
	FLAG_T = 1;
}


void TIMER_Init(uint8_t ms){
	tickConfig(ms);
}

uint8_t TIMER_Dispatch_Task(){
	tickCallbackSet( myTickHook, (void*)NULL );
	if(FLAG_T){
		FLAG_T = 0;
		MEF_update();
	}
}

