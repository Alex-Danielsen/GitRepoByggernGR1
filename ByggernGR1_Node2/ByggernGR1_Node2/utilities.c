/*
 * utilities.c
 *
 * Created: 25.10.2016 15:54:48
 *  Author: nikolasn
 */ 

#include "servo.h"

uint16_t utilities_joyToServo(uint8_t joyVal) {
	//switch to math without integers
	double newVal = (double)joyVal;
	
	//Go from 0-255 -> 0-1
	newVal /= 255;
	
	//Go from 0-1 -> 0-(HIGH_VAL-LOW_VAL)
	newVal *= (HIGH_VAL-LOW_VAL);
	
	//Go from 0-(HIGH_VAL-LOW_VAL) -> LOW_VAL-HIGH_VAL
	newVal += LOW_VAL;
	
	return (uint16_t)newVal;
}

int16_t utilities_joyToMotor(uint8_t joyVal) {
	//switch to math without integers
	double newVal = (double)joyVal;
	
	//Go from 0-255 -> 0-510
	newVal *= 2;
	
	//Go from 0-510 -> -255-255
	newVal -= 255;
	
	//Clamp end values
	if(newVal < -200) {
		newVal = -200;
	}
	else if(newVal > 200) {
		newVal = 200;
	}
	
	return (int16_t)newVal;
}