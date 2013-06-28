#include "Wire.h"

int accel[3];
int gyro[3];

//Accelerometer Address: 0x19
//Gyro Address: 0x1E?

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  
  //Enable Accel
  Wire.beginTransmission(0x19);
  Wire.write(0x20);
  Wire.write(0x27);
  Wire.endTransmission();
}

void loop()
{
   Wire.beginTransmission(0x1E);
   Wire.write(0x28);
   Wire.endTransmission();
   Wire.requestFrom(0x1E, 6);
   for(char i = 0; i < 3; i++)
   {
     gyro[i] = Wire.read()*256 + Wire.read();
   }
   
   Wire.beginTransmission(0x19);
   Wire.write(0x28);
   Wire.endTransmission();
   Wire.requestFrom(0x19, 6);
   for(char i = 0; i < 3; i++)
   {
     while(Wire.available()==0){}
     accel[i] = Wire.read()*256 + Wire.read();
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
