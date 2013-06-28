#include "Wire.h"

char data[6];

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(0x19);
  Wire.write(0x20);
  Wire.write(0x27);
  Wire.endTransmission();
}

void loop()
{
  
  /* This code works as intended */
  /*
  for(int i = 0; i<6; i++)
  {
   Wire.beginTransmission(0x19);
   Wire.write(0x28+i);
   Wire.endTransmission();
   Wire.requestFrom(0x19, 1);
   data[i] = Wire.read();
  }
  */
  
  /* This code causes all 6 values to be the same */
  Wire.beginTransmission(0x19);
  Wire.write(0x28);
  Wire.endTransmission();
  Wire.requestFrom(0x19, 6);
  
  for(int i = 0; i<6; i++)
    data[i] = Wire.read();  
  for(int i = 0; i<6; i++)
  {
    Serial.print(data[i],HEX);
    Serial.print(" ");
  }
  Serial.println();
  delay(1000);
}
