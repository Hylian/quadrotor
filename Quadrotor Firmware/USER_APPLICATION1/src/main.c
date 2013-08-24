
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
	
	struct PIDobject xPID;
	struct PIDobject yPID;
	
	
	//TODO: Find the value for these
	SetTunings(xPID, 5, 0, 0);
	SetTunings(yPID, 5, 0, 0);
	SetOutputLimits(xPID, 0, 100);
	SetOutputLimits(yPID, 0, 100);
	
	for(;;)
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
			setMotorSpeed(MotorD0, 50+xPID.Output);
			setMotorSpeed(MotorD1, 50-xPID.Output);
			setMotorSpeed(MotorE0, 50+yPID.Output);
			setMotorSpeed(MotorE1, 50-yPID.Output);
		}
		if(/*radio update*/)
		{
			//Process radio packet
		}
	}
	
}
