status_code_t twiWrite(char busAddress, char writeAddress, char* dataPtr, char length);
status_code_t twiRead(char busAddress, char readAddress, char* dataPtr, char length);