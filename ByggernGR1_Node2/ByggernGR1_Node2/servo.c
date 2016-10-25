/*
 * servo.c
 *
 * Created: 25.10.2016 13:56:55
 *  Author: nikolasn
 */ 

#include <avr/io.h>
#include "servo.h"
void servo_init(){
	
	DDRB |= (1 << PB5); //Set PWM pin output
	
	TCCR1B |= (1 << CS11); //Start timer/counter with prescaler = 8
	
	TCCR1A |= (1 << COM1A1); //Clear OC1A on compare match
	
	TCCR1A |= (1 << WGM11); //for FastPWM
	TCCR1B |= (1 << WGM12) | (1 << WGM13); //for FastPWM
	
	ICR1 = 39999; //Set frequency to 50Hz
	
	OCR1A = MID_VAL; // Set servo to the middle (1.5ms)
}

void servo_set(uint16_t inVal) {
	//clamp servo positions between it's lowest and highest values
	if (inVal < LOW_VAL) {
		OCR1A = LOW_VAL; 
	}
	else if(inVal > HIGH_VAL) {
		OCR1A = HIGH_VAL;
	}
	else{
		OCR1A = inVal;
	}
}