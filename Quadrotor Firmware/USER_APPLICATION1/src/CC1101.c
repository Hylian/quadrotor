#include "CC1101.h"
#include "CC1101Cfg.h"
#include "SPICfg.h"

//Rewrite it all with spi single write not packet http://asf.atmel.com/docs/3.8.1/xmegaa/html/group__xmega__spi__master__group.html
status_code CCRead(char addr, char* data)
{
	status_code result;
	char
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	result = spi_write_packet(&SPID, addr|0x80, 1);
	spi_read_packet(&SPIC, *data, 1);
	spi_deselect_device(&SPIC, &spi_device_conf);
	return result;
};

status_code CCReadBurst(char addr, char* dataPtr, char size)
{
	status_code result;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	result = spi_write_packet(&SPID, addr|0xC0, 1);
	spi_read_packet(&SPIC, *dataPrt, size);	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return result;
}

status_code CCWrite(char addr, char data)
{
	status_code result;
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	result = spi_write_packet(&SPID, addr|0xC0, 1);
	
}