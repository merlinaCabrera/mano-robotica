/*
 * mef.c
 *
 *  Created on: 1 oct. 2023
 *      Author: User
 */
#include "sapi.h"
#include "mef.h"
#include "usb.h"
#include "resolucion.h"

#define LED_ROJO GPIO1
#define LED_VERDE GPIO3
#define LED_AZUL GPIO7

uint8_t WAIT_FLAG = 0;
uint8_t BUTTON_FLAG = 0;
char initMsg, levelMsg;
char dataFromUart [5];
char aux [5] = "00000";
bool_t estado_boton;
states actState;



// Defno los niveles de resolucion y el angulo que girará el servo
// EL final será 2^level niveles distintos de giro
uint8_t level = 0, angulo = 0;

void girarServo(uint8_t servo, uint8_t angulo){
	switch (servo){
		case 0:
			servoWrite(SERVO8, angulo);
			break;
		case 1:
			servoWrite(SERVO4, angulo);
			break;
		case 2:
			servoWrite(SERVO1, angulo);
			break;
		case 3:
			servoWrite(SERVO2, angulo);
			break;
		case 4:
			servoWrite(SERVO3, angulo);
			break;

	}
}



void MEF_init(){
	actState=START;
	 gpioConfig(LED_ROJO, GPIO_OUTPUT);
	 gpioConfig(LED_VERDE, GPIO_OUTPUT);
	 gpioConfig(LED_AZUL, GPIO_OUTPUT);
	gpioConfig(GPIO7, GPIO_INPUT);
}

void MEF_update(){ 		//Cada 1 ms
static uint16_t call_count_led = 0;
static uint16_t call_count_mef = 0;
static uint16_t call_count = 0;
static bool_t LEDB_state = OFF;
static uint8_t i=0, first_time = 1, j=0;


	switch (actState){
		case START:
			USB_init();
			actState = CONNECTING;

		break;
		case CONNECTING:
			if(++call_count_led == 500){	//0.5 s
				gpioToggle(LED_VERDE);
				call_count_led = 0;
			}
			if(++call_count_mef == 30000){	//30 s
				call_count_mef=0;
				actState = FAIL;
			}
			if(uartReadByte(UART_USB, &initMsg)){	//Espero mensaje de comienzo de comunicacion
				if(initMsg == 'a'){
					// se deberá esperar un aX (donde X = 1, 2, 3, 4, 5, 6, 7, 8)
					if(uartReadByte(UART_USB, &levelMsg)){
						level = definirNiveles(levelMsg);
						gpioWrite(LED_AZUL, OFF);
						call_count_mef = 0;
						actState = SUCCESS1;
						uartWriteByte(UART_USB, 'c');
					}
				}
			}

		break;
		case SUCCESS1:
			gpioWrite(LED_VERDE, ON);

			if(++call_count_mef == 1000){
				call_count_mef = 0;
				gpioWrite(LED_VERDE, OFF);
				actState = WAITING;
			}

		break;
		case FAIL:
			gpioWrite(LED_ROJO, ON);
			if(++call_count_mef == 10000){
				call_count_mef = 0;
				gpioWrite(LED_ROJO, OFF);
				actState = CONNECTING;
			}

		break;
		case WAITING:
			gpioWrite(LED_AZUL, ON);
			if(uartReadByte(UART_USB, &dataFromUart[i])){
				i++;
			}
			estado_boton= gpioRead(GPIO7);
			if(!(estado_boton)){
				BUTTON_FLAG = 1;
				//actState = CONNECTING;
				//gpioWrite(LED_AZUL, OFF);
			}
			if(i == 5){
				gpioWrite(LED_AZUL, OFF);
				call_count_mef = 0;
				i=0;
				if(BUTTON_FLAG){
					actState = CONNECTING;
					BUTTON_FLAG = 0;
				} else {
					actState = CONTROLLING;
				}
			}

		break;

		case CONTROLLING:
			gpioWrite(LED_VERDE, ON);
			/*if(first_time){
				first_time = 0;
				while (j < 5){
					if(aux[j] != dataFromUart[j]){
						uartWriteByte(UART_USB, dataFromUart[j]);
						uartWriteByte(UART_USB, aux[j]);
						angulo = AnguloDeGiro(dataFromUart[j],0,level);
						girarServo(j, angulo);
						aux[j] = dataFromUart[j];
					}
					j++;

				}
				j = 0;

			}*/
			if(first_time){
				first_time = 0;
				for(uint8_t j=0; j<5; j++){
					if (j == 0) {
						angulo = AnguloDeGiroPulgar(dataFromUart[j],0,level);
					} else {
						angulo = AnguloDeGiro(dataFromUart[j],0,level);
					}
					girarServo(j, angulo);
				}
			}
			if(++call_count_mef == 200){
				first_time = 1;
				gpioWrite(LED_VERDE, OFF);
				call_count_mef = 0;
				uartWriteByte(UART_USB, 'c');
				// A modo de ejemplo, solamente tomo en cuenta el primero de los 5 elementos

				actState = WAITING;
			}
		break;
		}
	}

