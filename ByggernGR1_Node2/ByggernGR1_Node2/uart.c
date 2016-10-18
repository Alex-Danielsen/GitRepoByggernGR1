/*
 * uart.c
 *
 * Created: 30.08.2016 14:23:15
 *  Author: Atmel
 */ 



#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>

void UART_init(int ubrr){
	//Set baud rate from input:
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	//Enable UART 0 receive (RXEN0) and transfer (TXEN0):
	UCSR0B |= (1 << RXEN0)|(1 << TXEN0);
	
	//Set register select (URSEL0), stop bit select (USBS0), character size (UCSZ00) and uart mode (UMSEL0):
	UCSR0C |=(3 << UCSZ00);
}

unsigned char UART_recieve(){
	//Wait for data by checking received flag (RXC0):
	while (!(UCSR0A & (1 << RXC0)));
	
	//Get data from buffer (UDR0) and return:
	return UDR0;
}

void UART_transmit(unsigned char arg){
	
	//Check if transmit buffer is ready to receive new data:
	while (!(UCSR0A & (1 << UDRE0)));
	
	//Put data in transmit buffer:
	UDR0 = arg;
}

void UART_parsePrint(){
	fdevopen(UART_transmit, UART_recieve);
}

void UART_test(){
	DDRA |= (1 << DDA0);
	char temp = 'a';
	while(1)
	{
		temp = UART_recieve();
		switch(temp){
		
			case 'a':{
				PORTA |= (1 << DDA0);
				break;
			}
			case 'b':{
				PORTA &= !(1 << DDA0);
				break;
			}
		
		}
	
	}
}