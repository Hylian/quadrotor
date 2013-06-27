#include "Wire.h"

int accel[3];
int gyro[3];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
   Wire.beginTransmission(0x1E);
   Wire.write(0x28);
   Wire.endTransmission();
   Wire.requestFrom(0x1E, 6);
   for(char i = 0; i < 3; i++)
   {
     accel[i] = Wire.read() << 8 | Wire.read();
   }
   
   Wire.beginTransmission(0x19);
   Wire.write(0x28);
   Wire.endTransmission();
   Wire.requestFrom(0x19, 6);
   for(char i = 0; i < 3; i++)
   {
     gyro[i] = Wire.read() << 8 | Wire.read();
   }
   
   Serial.println();
   Serial.print("Accel: ");
   Serial.print(accel[0]);
   Serial.print(" ");
   Serial.print(accel[1]);
   Serial.print(" ");
   Serial.print(accel[2]);
   Serial.print(" Gyro: ");
   Serial.print(gyro[0]);
   Serial.print(" ");
   Serial.print(gyro[1]);
   Serial.print(" ");
   Serial.print(gyro[2]);
   
   delay(1000);
  
}
