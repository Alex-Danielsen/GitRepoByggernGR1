/*
 * uart.h
 *
 * Created: 30.08.2016 14:23:26
 *  Author: nikolasn
 */ 


#ifndef UART_H_
#define UART_H_

//---FUNCTIONS---
void UART_init(int ubrr);

unsigned char UART_recieve();

void UART_transmit(unsigned char arg);

void UART_parsePrint();

void UART_test();

#endif /* UART_H_ */