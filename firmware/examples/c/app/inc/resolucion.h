/*
 * RESOLUCION.C
 */

#ifndef _RESOLUCION_H_
#define _RESOLUCION_H_

// Define los pasos totales que podr� girar el servo
uint8_t definirNiveles(char);

// A partir de los pasos, define un �bgulo adecuado
uint8_t AnguloDeGiro(char, uint8_t, uint8_t);
uint8_t AnguloDeGiroPulgar(char, uint8_t, uint8_t);

// Funci�n Potencia
uint8_t potencia(uint8_t, uint8_t);

// Redondeo al entero m�s cercano
uint8_t redondeo(double);

#endif
