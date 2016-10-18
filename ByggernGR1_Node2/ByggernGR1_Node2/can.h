/*
 * can.h
 *
 * Created: 04.10.2016 16:27:21
 *  Author: nikolasn
 */ 


#ifndef CAN_H_
#define CAN_H_

//---LIBRARIES---
#include <avr/io.h>

//---TYPEDEFS---
//CAN message struct:
typedef struct {
	uint16_t id; //Only support 8 bit addresses 
	uint8_t length; //Only 4 least significant bits used
	char data[8];
} can_message;

//---FUNCTIONS---
void can_init();

void can_send(can_message*);

can_message can_recieve();

#endif /* CAN_H_ */