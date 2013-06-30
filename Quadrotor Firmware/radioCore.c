#include "radioCore.h"

void transmitData(char *txData, char len, char srcAddress, char destAddress)
{
	char stat;
	CCWrite(CC1101_TXFIFO, len+2);
	CCWrite(CC1101_TXFIFO, destAddress);
	CCWrite(CC1101_TXFIFO, srcAddress);
	CCWriteBurst(CC1101_TXFIFO, txData, len);
	CCStrobe(CC1101_STX);
	while(1)
	{
		char size;
		stat = CCRead(CC1101_TXBYTES, &size);
		if( size == 0 )
			break;
		else
			CCStrobe(CC1101_STX);
	}
}

char txFifoFree()
{
	char stat;
	char size;
	
	stat = CCRead(CC1101_TXBYTES, &size);
	if (size >= 64)
	{
		CCStrobe(CC1101_SFTX);
		stat = CCRead(CC1101_TXBYTES, &size);
	}
	return (CC1101_FIFO_SIZE - size);
}

int receiveData(char *rxData, char *len, char *srcAddress, char *destAddress, char *rssi, char *lqi)
{
	stat = CCRead(CC1101_RXFIFO, len);
	CCRead(CC1101_RXFIFO, destAddress);
	CCRead(CC1101_RXFIFO, srcAddress);
	*len -= 2;
	CCReadBurst(CC1101_RXFIFO, rxData, *len);
	CCRead(CC1101_RXFIFO, rssi);
	*rssi = CCRSSIdecode(*rssi);
	stat = CCRead(CC1101_RXFIFO, lqi);
	
	if((*lqi & 0x80) == 0)
		return NOTHING;
	*lqi = *lqi & 0x7F;
	
	if ((stat & 0xF0) == 0x60){ 
		errNo=3; //Error RX overflow
		CCStrobe(CC1101_SFRX); // flush the RX buffer
		return ERR;
	}
	return OK;
}