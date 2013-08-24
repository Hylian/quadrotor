#ifndef _PID_H
#define _PID_H

struct PIDobject
{
	double Output, Setpoint;
	double ITerm, lastInput;
	double kp, ki, kd;
	int SampleTime = 20; // 50 Hz
	double outMin, outMax;
};

void computePID(PIDobject p, double Input);
void SetTunings(PIDobject p, double Kp, double Ki, double Kd);
void SetOutputLimits(PIDobject p, double Min, double Max);

#endif