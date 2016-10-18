/*
 * mcp.c
 *
 * Created: 04.10.2016 15:06:14
 *  Author: nikolasn
 */ 

#include "spi.h"
#include "MCP2515_macros.h"
#include <avr/io.h>
#include <avr/delay.h>

void mcp_init(){
	
	
	
	// Data direction of Chip Select pin
	DDRB |= (1 << PB7);
	// Set CS high
	PORTB |= (1 << PB7);
	
	// Initialize SPI
	spi_init();	
	
	//Highly recommended to reset after power on
	mcp_reset();
	
}


char mcp_read(char address){
	PORTB &= ~(1 << PB7);
	spi_transmit(MCP_READ);
	spi_transmit(address);
	spi_transmit(0x00); //Generate clock pulses to receive data
	PORTB |= (1 << PB7);
	return spi_read();
}

void mcp_write(char address, char data){
	PORTB &= ~(1 << PB7);  
	spi_transmit(MCP_WRITE);
	spi_transmit(address);
	spi_transmit(data);
	PORTB |= (1 << PB7);
	
}

void mcp_requestSend(uint8_t transmitBuffers){ 
	//transmitBuffers individual bits decides which buffers to use
	//For example, 111 uses all of the bits, while 000 uses none
	//order is TB2, TB1, TB0
	PORTB &= ~(1 << PB7);
	uint8_t instruction = 0x80+transmitBuffers; //convert to correct instruction format: 10000(TB2)(TB1)(TB0) 
	spi_transmit(0b10000001);
	PORTB |= (1 << PB7);
}

char mcp_readStatus(){
	PORTB &= ~(1 << PB7);
	spi_transmit(MCP_READ_STATUS); //command to read status
	spi_transmit(0x00); //anything - just send something to get info back on the bus
	PORTB |= (1 << PB7);
	return spi_read();
}

void mcp_bitModify(uint8_t address, uint8_t mask, char data){
	PORTB &= ~(1 << PB7);
	spi_transmit(MCP_BITMOD);
	spi_transmit(address);
	spi_transmit(mask);
	spi_transmit(data);
	PORTB |= (1 << PB7); 
}

void mcp_reset(){
	PORTB &= ~(1 << PB7);
	spi_transmit(MCP_RESET);
	_delay_ms(10);
	PORTB |= (1 << PB7);
}