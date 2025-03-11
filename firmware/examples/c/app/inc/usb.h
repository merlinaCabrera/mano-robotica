#ifndef _USB_H_
#define _USB_H_
#include "sapi.h"

//Inicializa la comunicacion
void USB_init(void);

//Lee un dato de la transmision en el caso de que lo haya, si recibio los 5 devuelve true, caso contrario, false
uint8_t USB_receiveArray();




#endif /* _USB_H_ */
