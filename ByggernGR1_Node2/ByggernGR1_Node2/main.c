/*
 * ByggernGR1_Node2.c
 *
 * Created: 18.10.2016 13:53:32
 *  Author: nikolasn
 */ 


#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "can.h"
#include "mcp.h"
#include "spi.h"

#define F_CPU 16000000
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

//Interupt service routine for MCP
ISR(INT4_vect){
	printf("Interrupt occurred...")
}

int main(void){	
	UART_init(MYUBRR);
	UART_parsePrint();
	can_init();
	
	//Setup interrupt for MCP
	//Set to falling edge
	EICRB |= (1 << ISC41);
	//Set mask
	EIMSK |= (1 << INT4);
	//Enable interupts - disable with cli()
	sei()
	 
	
	//BEGIN CAN TEST:
	volatile can_message newMessage = {
		.id = 0x00,
		.length = 1,
		.data[0] = 23,
	};
	
	can_send(&newMessage);
	_delay_ms(100);
	volatile can_message recMessage = can_recieve();
	printf("DATA: %d\n",(recMessage.data[0]));
	//END CAN TEST.
    while(1){
    }
}