/*
 * timer.h
 *
 *  Created on: 10 oct. 2023
 *      Author: User
 */


#ifndef EXAMPLES_C_APP_INC_TIMER_H_
#define EXAMPLES_C_APP_INC_TIMER_H_

#include "sapi.h"

void TIMER_Init(uint8_t);			//Inicializa los tick del sistema el cual cada x ms pasados por parametro, genera una callback
uint8_t TIMER_Dispatch_Task(void );	//Lee estados de flag y ejecuta tarea correspondiente



#endif /* EXAMPLES_C_APP_INC_TIMER_H_ */
