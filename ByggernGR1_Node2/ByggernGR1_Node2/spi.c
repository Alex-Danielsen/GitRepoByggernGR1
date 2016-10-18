/*
 * spi.c for Atmega2560
 *
 * Created: 04.10.2016 14:11:30
 *  Author: nikolasn
 */ 
#include <avr/io.h>


void spi_init(){
	// set data direction on SPI pins
	DDRB |= (1 << DDB1)|(1 << DDB2);
	
	// Chip select pin set high:
	DDRB |= (1 << DDB0)|(1<<DDB7);
	PORTB |= (1 << DDB0);
	
	// Set mode to "Master"
	SPCR |= (1 << MSTR);
	// Set clock rate to fck/16
	SPCR |= (1 << SPR0);
	// Enable SPI
	SPCR |= (1 << SPE);
	
	
}



void spi_transmit(char data){
	
	// Inputs data, start transmission
	SPDR = data;
	
	// Checks transmission complete flag
	while(!(SPSR & (1 << SPIF))){}
	
}

char spi_read() {
	return SPDR;
}


