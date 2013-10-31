#include "PID.h"

//http://brettbeauregard.com/blog/2011/04/improving-the-beginner¡¯s-pid-reset-windup/

void computePID(PIDobject* p, double Input) //Will be called every 20 ms due to ISR
{
	double error = *p.Setpoint - Input;
	*p.ITerm += (*p.ki *error);
	if(*p.ITerm > *p.outMax)
		*p.ITerm = *p.outMax;
	else if(*p.ITerm < *p.outMin)
		*p.ITerm = *p.outMin;
	double dInput = (Input - *p.lastInput);
	
	*p.Output = *p.kp * error + *p.ITerm - *p.kd * dInput;
	if(*p.Output > *p.outMax)
		*p.Output = *p.outMax;
	else if(*p.Output < *p.outMin)
		*p.Output = *p.outMin;
		
	*p.lastInput = Input;	
}

void SetTunings(PIDobject* p, double Kp, double Ki, double Kd)
{
	double SampleTimeInSec = ((double)*p.SampleTime)/1000;
	*p.kp = Kp;
	*p.ki = Ki * SampleTimeInSec;
	*p.kd = Kd / SampleTimeInSec;
}

void SetOutputLimits(PIDobject* p, double Min, double Max)
{
	if(Min > Max) return;
	*p.outMin = Min;
	*p.outMax = Max;
	
	if(*p.Output > *p.outMax) *p.Output = *p.outMax;
	else if(*p.Output < *p.outMin) *p.Output = *p.outMin;

	if(*p.ITerm> *p.outMax) *p.ITerm= *p.outMax;
	else if(*p.ITerm< *p.outMin) *p.ITerm= *p.outMin;
}