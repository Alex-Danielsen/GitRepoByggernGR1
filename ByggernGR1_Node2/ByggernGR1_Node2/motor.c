/*
 * motor.c
 *
 * Created: 01.11.2016 13:39:54
 *  Author: nikolasn
 */ 

#include <avr/io.h>
#include <avr/delay.h>

#include "TWI_master.h"
#include "motor.h"

void motor_init(){
	TWI_Master_Initialise();
	//Set DDHx bits in data direction register DDRH to set pin x on PORTH as output:
	DDRH |= (1 << DDH1);	//DIR pin
	DDRH |= (1 << DDH3);	//SEL pin
	DDRH |= (1 << DDH4);	//EN pin
	DDRH |= (1 << DDH5);	//!0E pin
	DDRH |= (1 << DDH6);	//RST pin
	
	
	//Set PINH4 bit in PORTH register to enable motor (PINH4 = EN pin):
	PORTH |= (1 << PINH4);
	
	//Reset the motor:
	motor_reset();
}


void motor_reset(){
	//Clear PINH5 bit in PORTH register to set RST signal thus resetting the motor:
	PORTH &= ~(1 << PINH6);
	_delay_ms(25); //Wait for motor to reset.
	//Set PINH5 bit in PORTH reg to clear RST signal.
	PORTH |= (1 << PINH6);
	printf("Encoder Reset\n");
}


int16_t motor_getEncoder(){
	int16_t encoderVal;
	
	//Set OE low to enable encoder output:
	PORTH &= ~(1 << DDH5);
	//Set SEL low to get high byte:
	PORTH &= ~(1 << DDH3);
	_delay_ms(20);
	encoderVal = PINK << 8; //Read high byte.
	//Set SEL high to get low byte:
	PORTH |= (1 << DDH3);
	_delay_ms(20);
	encoderVal += PINK; //Read low byte.
	
	//Set OE high to disable encoder output:
	PORTH |= (1 << DDH5);
	
	//Return encoder values:
	return encoderVal;
}


void motor_setDir(motorDir_t dir){
	switch(dir){
		case LEFT:
			//Clear DIR pin:
			PORTH &= ~(1 << PINH1);
			break;
		case RIGHT:
			//Set DIR pin:
			PORTH |= (1 << PINH1);
			break;
	}
}


void motor_setSpeed(char speed){
	unsigned char twiMsg [3];
	twiMsg[0] = 0x5E;
	twiMsg[1] = 0x00;
	twiMsg[2] = speed;
	
	//Wait for TWI Transciever:
	while(TWI_Transceiver_Busy());
	TWI_Start_Transceiver_With_Data(twiMsg,3);
	
	
}


/*
*
* inVal - Assumed to be between -255 and 255
*/
void motor_joyControl(int16_t inVal) {
	
	if(inVal < -10) {
		motor_setDir(RIGHT);
		motor_setSpeed(-1*inVal);
	}
	else if(inVal > 10) {
		motor_setDir(LEFT);
		motor_setSpeed(inVal);		
	}
	else {
		motor_setSpeed(0);
	}
	
}

//Drive motor left until the encoder values stop changing
void motor_calibrate() {
	motor_setDir(RIGHT);
	int16_t prevEnc = 3000;
	int16_t Enc = 0;
	motor_setSpeed(90);
	while(prevEnc != motor_getEncoder()) {
		printf("Driving left!\n");
		Enc = motor_getEncoder();
		_delay_ms(100);
		prevEnc = Enc;
	}
	motor_setSpeed(0);
	printf("Stop Motor!\n");
	
	_delay_ms(3000);
	
	//Reset the motor:
	motor_reset();
}