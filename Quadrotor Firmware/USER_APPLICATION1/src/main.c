
/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <math.h>
#include "motor.h"
#include "LSM303D.h"
#include "L3G4200D.h"
#include "radioCore.h"
#include "kalman.h"
#include "radioCommand.h"

#define ACCEL_SCALE 1
#define GYRO_SCALE 1

int main (void)
{
	board_init();
	//PowerOnStartUp();
	accelSetup();
	gyroSetup();
	CCSetup();
	
	int xangletemp, yangletemp, zangletemp, xratetemp, yratetemp, zratetemp;
	double roll, pitch;
	int throttle;
	
	struct PIDobject xPID;
	struct PIDobject yPID;
	
	
	//TODO: Find the value for these
	SetTunings(xPID, 5, 0, 0);
	SetTunings(yPID, 5, 0, 0);
	SetOutputLimits(xPID, -20, 20);
	SetOutputLimits(yPID, -20, 20);
	
	while(1)
	{
		if(/*control update*/)
		{
			//Read Sensors
			accelRead(xangletemp, yangletemp, zangletemp);
			gyroRead(xratetemp, yratetemp, zratetemp);
			
			//Normalize Sensor Data
			/*
			xangletemp *= ACCEL_SCALE;
			yangletemp *= ACCEL_SCALE;
			zangletemp *= ACCEL_SCALE;
			*/
			roll = atan(xangletemp/sqrt(yangletemp*yangletemp + zangletemp*zangletemp));
			pitch = atan(yangletemp/sqrt(xangletemp*yangletemp + zangletemp*zangletemp));
			
			xratetemp *= GYRO_SCALE;
			yratetemp *= GYRO_SCALE;
			zratetemp *= GYRO_SCALE;
			
			//Update Kalman
			updateKalman((double)roll, (double)pitch, (double)xratetemp, (double)yratetemp);
			//Update PID
			computePID(xPID, xangle);
			computePID(yPID, yangle);
			
			//Update Motors
			setMotorSpeed(MotorD0, throttle + xPID.Output);
			setMotorSpeed(MotorD1, throttle - xPID.Output);
			setMotorSpeed(MotorE0, throttle + yPID.Output);
			setMotorSpeed(MotorE1, throttle - yPID.Output);
		}
		if(/*radio update*/)
		{
			
			processCommand(/*payload*/, /*bytes*/, xPID, yPID, )
		}
	}
	
}
