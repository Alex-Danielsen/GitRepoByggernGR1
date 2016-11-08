/*
 * motor.h
 *
 * Created: 01.11.2016 13:40:08
 *  Author: nikolasn
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

typedef enum motorDir{
	LEFT,
	RIGHT	
} motorDir_t;

void motor_init();
void motor_reset();
int16_t motor_getEncoder();
void motor_setDir(motorDir_t dir);
void motor_setSpeed(char speed);
void motor_joyControl(int16_t rawJoyVal);
void motor_calibrate();




#endif /* MOTOR_H_ */