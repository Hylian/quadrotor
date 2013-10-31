#include "L3G4200D.h"
#include "TWICfg.h"
#include "TWI.h"

void gyroSetup(void)
{
	#ifndef _TWI_INITIALIZED
	#define _TWI_INITIALIZED
	twi_init();
	#endif
	twiWrite(GYRO_ADDR, CTRL_REG1, 0x5F, 1);
	/*
		Datasheet Page: 29
		ODR: 200 Hz
		BW Cut-Off: 25
		Power Down: Normal Mode (1)
		Xen, Yen, Zen: 1
	*/
}

void gyroRead(int* xPtr, int* yPtr, int* zPtr)
{
	char temp_data[6];
	while(twiRead(GYRO_ADDR, OUT_X_L, &temp_data, 6) != STATUS_OK);
	*xPtr = temp_data[0] + temp_data[1] * 256;
	*yPtr = temp_data[2] + temp_data[3] * 256;
	*zPtr = temp_data[4] + temp_data[5] * 256;
}