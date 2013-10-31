//http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/DM00057547.pdf

#include "LSM303D.h"
#include "TWICfg.h"
#include "TWI.h"

void accelSetup(void)
{
	#ifndef _TWI_INITIALIZED
	#define _TWI_INITIALIZED
	twi_init();
	#endif
	
	while(twiWrite(ACCEL_ADDR, CTRL1, 0x77, 1) != STATUS_OK);
	/*
		Datasheet Page: 35
		AODR (Data Rate Selection): 200 Hz
		AZEN: 1
		AYEN: 1
		AXEN: 1
	*/	
}

void accelRead(int* xPtr, int* yPtr, int* zPtr)
{
	char temp_data[6];
	while(twiRead(ACCEL_ADDR, OUT_X_L_A, &temp_data, 6) != STATUS_OK);
	*xPtr = temp_data[0] + temp_data[1] * 256;
	*yPtr = temp_data[2] + temp_data[3] * 256;
	*zPtr = temp_data[4] + temp_data[5] * 256;	
}