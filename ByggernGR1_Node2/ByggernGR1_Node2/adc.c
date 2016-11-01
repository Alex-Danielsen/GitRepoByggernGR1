/*
 * adc.c
 *
 * Created: 01.11.2016 12:58:06
 *  Author: nikolasn
 */ 
#include <avr/io.h>

void adc_init(){
	
	//Set bit ADPS0, ADPS1 and ADPS2 in ADCSRA to set prescaler to 128:
	ADCSRA |= (1 << ADPS0);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS2);
	
	//NOT SURE:
	ADMUX |= (1 << REFS0);
	
	//Set bit ADEN in ADC Control and status register ADCSRA to enable ADC:
	ADCSRA |= (1 << ADEN);
}



uint16_t adc_read(){
	//Set bit ADSC in ADC Control and status register to start conversion:
	ADCSRA |= (1 << ADSC);
	
	//Wait until conversion is complete by checking ADIF bit in ADCSRA:
	while(!(ADCSRA & (1 << ADIF)))
	
	//Return the ten first bits of the result from conversion stored in ADC:
	return ADC & 0x03FF;
}