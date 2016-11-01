/*
 * ir.c
 *
 * Created: 25.10.2016 17:34:06
 *  Author: nikolasn
 */ 


#include <avr/io.h>


void ir_init() {
	PORTF |= (1 << PINF0);
	
	
}