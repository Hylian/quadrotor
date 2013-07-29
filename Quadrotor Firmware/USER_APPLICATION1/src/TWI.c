#include "TWI.h"

status_code_t twiWrite(char busAddress, char writeAddress, char data, char length)
{
	twi_package_t packet_write =
	{
		.addr			= writeAddress,
		.addr_length	= sizeof (uint16_t),
		.chip			= busAddress;
		.buffer			= &data,
		.length			= length
	};
	
	return twi_master_write(&TWIM0, packet_write);
}

status_code_t twiRead(char busAddress, char readAddress, char* dataPtr, char length)
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