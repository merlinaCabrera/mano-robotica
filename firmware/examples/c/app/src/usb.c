#include "usb.h"
#include "sapi.h"

uint8_t FLAG_WAIT;
//char data_array[5] = {0};

void USB_init(){

	FLAG_WAIT=0;
	uartInit(UART_USB, 115200);

}

uint8_t USB_receiveArray(char* arreglo){
	static uint16_t dataCount=0;
	static uint8_t i=0;
	if( uartReadByte(UART_USB, &arreglo[i++]) ){
		dataCount++;
	}
	if(dataCount==5){
		i=0;
		dataCount=0;
		return 1;
	} else {
		return 0;
	}
}


void USB_sendFlagWait(){


}
