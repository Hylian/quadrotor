#ifndef _RADIOCOMMAND_H
#define _RADIOCOMMAND_H

#define RADIO_CONTROL 0
#define RADIO_SET_PID_X 1
#define RADIO_SET_PID_Y 2

void processCommand(char* payload, char bytes, PIDobject* xPID, PIDobject* yPID, char* throttle);

#endif
