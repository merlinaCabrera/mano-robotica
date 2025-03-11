/*
 * RESOLUCION.C
 */

#ifndef _RESOLUCION_H_
#define _RESOLUCION_H_

// Define los pasos totales que podrá girar el servo
uint8_t definirNiveles(char);

// A partir de los pasos, define un ábgulo adecuado
uint8_t AnguloDeGiro(char, uint8_t, uint8_t);
uint8_t AnguloDeGiroPulgar(char, uint8_t, uint8_t);

// Función Potencia
uint8_t potencia(uint8_t, uint8_t);

// Redondeo al entero más cercano
uint8_t redondeo(double);

#endif
