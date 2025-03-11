#include "sapi.h"


uint8_t potencia(uint8_t b, uint8_t e){
	uint8_t aux = b;
	for (int i = 1; i<e; i++){
		b = b*aux;
	}
	return b;
}

uint8_t redondeo(double x){
	double entero = (int)x;
	double fraccion = x-entero;

	if (fraccion < 0.5){
		return entero;
	} else {
		return entero + 1;
	}
}

uint8_t definirNiveles(char n){
	uint8_t n_numero = (int)n - '0';
	return (potencia(2,n_numero)-1);
}

uint8_t AnguloDeGiro(char dedo, uint8_t min, uint8_t max){
	uint8_t dedo_numero = (int)dedo -'0';
	if (dedo_numero > max){
		return 180;
	} else {
		return redondeo(dedo_numero*180/max);
	}
}

uint8_t AnguloDeGiroPulgar(char dedo, uint8_t min, uint8_t max){
	uint8_t dedo_numero = (int)dedo -'0';
	if (dedo_numero > max){
		return 90;
	} else {
		return redondeo(dedo_numero*90/max);
	}
}
