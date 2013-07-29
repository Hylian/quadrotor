#ifndef _MOTOR_H
#define _MOTOR_H

#define MotorD0 0
#define MotorD1 1
#define MotorE0 2
#define MotorE1 3

/* Function Prototypes */
void configPWM(void);
void startPWM(void);
void setMotorSpeed(char motor, char speed);

#endif