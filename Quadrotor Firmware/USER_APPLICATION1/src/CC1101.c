#include "CC1101.h"
#include "CC1101Cfg.h"
#include "SPICfg.h"

//http://asf.atmel.com/docs/3.8.1/xmegaa/html/group__xmega__spi__master__group.html

void CCRead(char addr, char* data)
{
	status_code result;
	char
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	spi_write_single(&SPIC, addr|0x80);
	spi_read_single(&SPIC, *data);
	spi_deselect_device(&SPIC, &spi_device_conf);
};

status_code CCReadBurst(char addr, char* dataPtr, char size)
{
	status_code result;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	spi_write_single(&SPIC, addr|0xC0);
	result = spi_read_packet(&SPIC, *dataPtr, size);	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return result;
}

void CCWrite(char addr, char data)
{
	status_code result;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	spi_write_single(&SPIC, addr);
	spi_write_single(&SPIC, data);
	spi_deselect_device(&SPIC, &spi_device_conf);
}

status_code CCWriteBurst(char addr, const char* dataPtr, char size)
{
	char result;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	spi_write_single(&SPIC, addr|0x40);
	result = spi_write_packet(&SPIC, *dataPtr, size);	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return result;
}

void CCStrobe(char addr)
{
	char result;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	spi_write_single(&SPIC, addr);
	spi_deselect_device(&SPIC, &spi_device_conf);	
}

void CCSetup()
{
	char reg;
	char val;
	for(char i = 0; i<CC1101_NR_OF_REGISTERS; i++)
	{
		reg = pgm_read_byte(&CC1101_registers[i]);
		val = pgm_read_byte(&CC1101_registerSettings[i]);
		CCWrite(reg, val);
	}
}

void CCsetPA(char paIndex)
{
	char PAval = pgm_read_byte(&CC1101_PATABLE[paIndex]);
	CCWrite(CC1101_PATABLE,PAval);
}

char CCRSSIdecode(char rssiEnc)
{
	char rssi;
	char rssiOffset = 74; // is actually dataRate dependant, but for simplicity assumed to be fixed.
	// RSSI is coded as 2's complement see section 17.3 RSSI of the cc1100 datasheet
	if (rssiEnc >= 128)
		rssi = (( rssiEnc - 256) >> 1) - rssiOffset;
	else
		rssi = (rssiEnc >> 1) - rssiOffset;
	return rssi;
}