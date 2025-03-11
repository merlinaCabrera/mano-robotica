/*============================================================================
 * Autor:
 * Licencia:
 * Fecha:
 *===========================================================================*/

// Inlcusiones

#include "app.h"         // <= Su propia cabecera
#include "sapi.h"        // <= Biblioteca sAPI
#include "timer.h"
#include "mef.h"

char dataArray[5]= {0};
uint8_t flagWait=0;
bool_t tec3Value = OFF;

#define SERVO_N SERVO0
/*
   SERVO0 <---> T_FIL1 de EDU-CIAA-NXP
   SERVO1 <---> T_COL0 de EDU-CIAA-NXP
   SERVO2 <---> T_FIL2 de EDU-CIAA-NXP
   SERVO3 <---> T_FIL3 de EDU-CIAA-NXP
   SERVO4 <---> GPIO8 de EDU-CIAA-NXP
   SERVO5 <---> LCD1 de EDU-CIAA-NXP
   SERVO6 <---> LCD2 de EDU-CIAA-NXP
   SERVO7 <---> LCD3 de EDU-CIAA-NXP
   SERVO8 <---> GPIO2 de EDU-CIAA-NXP
*/

#define LED_ROJO GPIO1
#define LED_VERDE GPIO3
#define LED_AZUL GPIO7

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void )
{
   // Configuraciones

   // Inicializar y configurar la plataforma

	boardConfig();


   servoConfig(4, SERVO_ENABLE);
   servoConfig(8, SERVO_ENABLE);
   servoConfig(1, SERVO_ENABLE);
   servoConfig(2, SERVO_ENABLE);
   servoConfig(3, SERVO_ENABLE);


   servoConfig(SERVO4, SERVO_ENABLE_OUTPUT);
   servoConfig(SERVO8, SERVO_ENABLE_OUTPUT);
   servoConfig(SERVO1, SERVO_ENABLE_OUTPUT);
   servoConfig(SERVO2, SERVO_ENABLE_OUTPUT);
   servoConfig(SERVO3, SERVO_ENABLE_OUTPUT);





   //Inicializar MEF y la temporizacion del programa
   MEF_init();
   TIMER_Init(1);

   gpioWrite(LED_ROJO,ON);

   uint16_t call_count=0;
   uint8_t i=0;


   //Bucle infinito
   while( TRUE ) {
	   TIMER_Dispatch_Task();

   }

   return 0;
}
