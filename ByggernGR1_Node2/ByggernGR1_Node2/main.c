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
#include "servo.h"
#include "utilities.h"

#define F_CPU 16000000
#define BAUD 9600
#define BAUDRATE F_CPU/16/BAUD-1

//Interrupt service routine for MCP
ISR(INT4_vect){
	printf("Interrupt occurred...");
	volatile can_message recMessage = can_recieve();
	printf("X: %d\n Y: %d \n",(recMessage.data[0]), (recMessage.data[1]));
	servo_set(utilities_joyToServo(recMessage.data[0]));
}
 
int main(void){	
	UART_init(BAUDRATE);
	UART_parsePrint();
	can_init();
	servo_init();
	
	
	/*  BEGIN INITIALIZATION OF INTERRUPTS */
	//Set to falling edge
	EICRB |= (1 << ISC41);
	//Set mask
	EIMSK |= (1 << INT4);
	//Enable interrupts - disable with cli()
	sei();
	/*  END INITIALIZATION OF INTERRUPTS */
	 printf("Init Complete");
	
	//BEGIN CAN TEST:
	volatile can_message newMessage = {
		.id = 0x00,
		.length = 1,
		.data[0] = 26,
	};
	
	//can_send(&newMessage);
	_delay_ms(100);
	
	//END CAN TEST.
	
	
    while(1){
    }
}