/*
 * solenoid.c
 *
 * Created: 01.11.2016 13:47:48
 *  Author: nikolasn
 */ 
#include <avr/io.h>
#include <avr/delay.h>

void solenoid_init(){
	//Set pin as output
	DDRF  |= (1 << DDF1);
	
	//Active high or low
	//PORTF |= (1 << PINF1);
	printf("Solenoid Init");
}


void solenoid_hit(){
	//set solenoid pin HIGH
	PORTF |= (1 << PINF1);
	//wait
	_delay_ms(1);
	//set solenoid pin LOW
	PORTF &= ~(1 << PINF1);
	
}
