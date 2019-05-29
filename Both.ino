#include <Wire.h>
#include "MAX30105.h"
#include <HMC5883L.h>

MAX30105 particleSensor;
HMC5883L compass;

void setup()
{
   // gy271
    Serial.begin(9600);
 Wire.begin();
 compass = HMC5883L();
// 
  Serial.begin(115200);
  Serial.println("Initializing...");

  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) 
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  byte ledBrightness = 0x1F; 
  byte sampleAverage = 8; 
  byte ledMode = 3; 
  int sampleRate = 100; 
  int pulseWidth = 411; 
  int adcRange = 4096; 

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); 
  
  const byte avgAmount = 64;
  long baseValue = 0;
  for (byte x = 0 ; x < avgAmount ; x++)
  {
    baseValue += particleSensor.getIR(); 
  }
  baseValue /= avgAmount;

  for (int x = 0 ; x < 500 ; x++)
    Serial.println(baseValue);

   
 
}

void loop()
{
  Serial.println(particleSensor.getIR()); 

  // gy 271
   MagnetometerRaw raw = compass.ReadRawAxis();
 MagnetometerScaled scaled = compass.ReadScaledAxis();
 float xHeading = atan2(scaled.YAxis, scaled.XAxis);
 float yHeading = atan2(scaled.ZAxis, scaled.XAxis);
 float zHeading = atan2(scaled.ZAxis, scaled.YAxis);
 if(xHeading < 0) xHeading += 2*PI;
 if(xHeading > 2*PI) xHeading -= 2*PI;
 if(yHeading < 0) yHeading += 2*PI; 
 if(yHeading > 2*PI) yHeading -= 2*PI;
 if(zHeading < 0) zHeading += 2*PI;
 if(zHeading > 2*PI) zHeading -= 2*PI;
 float xDegrees = xHeading * 180/M_PI;
 float yDegrees = yHeading * 180/M_PI;
 float zDegrees = zHeading * 180/M_PI;
 Serial.print(xDegrees);
 Serial.print(",");
 Serial.print(yDegrees);
 Serial.print(",");
 Serial.print(zDegrees);
 Serial.println(";");
 delay(100);
 
}
