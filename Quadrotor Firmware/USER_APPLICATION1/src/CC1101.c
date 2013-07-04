#include "CC1101.h"
#include "CC1101Cfg.h"
#include "SPICfg.h"

//http://asf.atmel.com/docs/3.8.1/xmegaa/html/group__xmega__spi__master__group.html
//Functions need to be modified to be full duplex so we can receive the stat byte

char CCRead(char addr, char* data)
{
	char stat;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	
	spi_write_single(&SPIC, addr|0x80);
	spi_read_single(&SPIC, stat)
	
	spi_write_single(&SPIC, CONFIG_SPI_MASTER_DUMMY);
	spi_read_single(&SPIC, data);
	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return stat;
};

char CCReadBurst(char addr, char* dataPtr, char size)
{
	char stat;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	
	spi_write_single(&SPIC, addr|0xC0);
	spi_read_single(&SPIC, stat);
	
	spi_read_packet(&SPIC, dataPtr, size);	
	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return stat;
}

char CCWrite(char addr, char data)
{
	char stat;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	
	spi_write_single(&SPIC, addr);
	spi_read_single(&SPIC, stat);
	
	spi_write_single(&SPIC, data);
	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return stat;
}

char CCWriteBurst(char addr, const char* dataPtr, char size)
{
	char stat;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	
	spi_write_single(&SPIC, addr|0x40);
	spi_read_single(&SPIC, stat);
	
	spi_write_packet(&SPIC, *dataPtr, size);	
	
	spi_deselect_device(&SPIC, &spi_device_conf);
	return stat;
}

char CCStrobe(char addr)
{
	char stat;
	spi_select_device(&SPIC, &spi_device_conf);
	while(PORTC.IN&PIN6_bm==PIN6_bm); //Wait for MISO to go low
	
	spi_write_single(&SPIC, addr);
	spi_read_single(&SPIC, stat);
	
	spi_deselect_device(&SPIC, &spi_device_conf);	
	return stat;
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