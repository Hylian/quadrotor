#include "radioCommand.h"
/*
union char2double
{
	char input[8];
	double output;
};
*/
void processCommand(char* payload, char bytes, PIDobject* xPID, PIDobject* yPID, char* throttle)
{
	switch(*payload)
	{
		case RADIO_CONTROL:
			&xPID.Setpoint = (double) &(payload+1);
			&yPID.Setpoint = (double) &(payload+1+sizeof(double));
			SetOutputLimits(xPID, (double) &(payload+1+sizeof(double)*2), (double) &(payload+1+sizeof(double)*2));
			SetOutputLimits(yPID, (double) &(payload+1+sizeof(double)*2), (double) &(payload+1+sizeof(double)*2));
		break;
		case RADIO_SET_PID_X:
			SetTunings(xPID, (double) &(payload+1), (double) &(payload+1+sizeof(double)), (double) &(payload+1+sizeof(double)*2));
		break;
		case RADIO_SET_PID_Y:
			SetTunings(yPID, (double) &(payload+1), (double) &(payload+1+sizeof(double)), (double) &(payload+1+sizeof(double)*2));
		break;
		
	}
};