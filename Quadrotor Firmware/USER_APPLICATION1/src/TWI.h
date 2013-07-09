status_code_t twiWrite(char writeAddress, char busAddress, char* dataPtr, char length);
status_code_t twiRead(char readAddress, char busAddress, char* dataPtr, char length);