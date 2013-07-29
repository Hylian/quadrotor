#ifndef _TWI_H
#define _TWI_H
status_code_t twiWrite(char busAddress, char writeAddress, char data, char length);
status_code_t twiRead(char busAddress, char readAddress, char* dataPtr, char length);
#endif