#ifndef RFBEECORE_H
#define RFBEECORE_H 1

#define OK 0
#define ERR -1
#define NOTHING 1
#define MODIFIED 2

#include "CC1101.h"

#include "radioCore.h"

void transmitData(char *txData, char len, char srcAddress, char destAddress);
char txFifoFree();
int receiveData(char *rxData, char *len, char *srcAddress, char *destAddress, char *rssi, char *lqi);


#endif