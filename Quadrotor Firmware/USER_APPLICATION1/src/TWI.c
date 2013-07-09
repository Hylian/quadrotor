#include "TWI.h"

status_code_t twiWrite(char writeAddress, char busAddress, char* dataPtr, char length)
{
	twi_package_t packet_write =
	{
		.addr			= writeAddress,
		.addr_length	= sizeof (uint16_t),
		.chip			= busAddress;
		.buffer			= dataPtr,
		.length			= length
	};
	
	return twi_master_write(&TWIM0, packet_write);
}

status_code_t twiRead(char readAddress, char busAddress, char* dataPtr, char length)
{
	twi_package_t packet_read =
	{
		.addr			= readAddress,
		.addr_length	= sizeof (uint16_t),
		.chip			= busAddress,
		.buffer			= dataPtr,
		.length			= length
		
	};
	
	return twi_master_read(&TWIM0, &packet_read);
}