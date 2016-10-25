/*
 * servo.h
 *
 * Created: 25.10.2016 13:57:05
 *  Author: nikolasn
 */ 


#ifndef SERVO_H_
#define SERVO_H_

//---LIBRARIES---
#include <avr/io.h>

#define SERVOPIN PB5
#define LOW_VAL 2000
#define MID_VAL 3000
#define HIGH_VAL 3900

void servo_init();

void servo_set(uint16_t inVal);




#endif /* SERVO_H_ */