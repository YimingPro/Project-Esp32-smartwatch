#include <Adafruit_HMC5883_U.h>
#include <HMC5883L.h>
HMC5883L compass;


#include "MAX30105.h"

#include "heartRate.h"

#include <Wire.h>
MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;


void setup()
{
   // gy271
    Serial.begin(9600);
 Wire.begin();
 compass = HMC5883L();
// 
//  Serial.begin(115200);
//  Serial.println("Initializing...");

//  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) 
//  {
//    Serial.println("MAX30105 was not found. Please check wiring/power. ");
//    while (1);
//  }
//
//  byte ledBrightness = 0x1F; 
//  byte sampleAverage = 8; 
//  byte ledMode = 3; 
//  int sampleRate = 100; 
//  int pulseWidth = 411; 
//  int adcRange = 4096; 
//
//  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); 
//  
//  const byte avgAmount = 64;
//  long baseValue = 0;
//  for (byte x = 0 ; x < avgAmount ; x++)
//  {
//    baseValue += particleSensor.getIR(); 
//  }
//  baseValue /= avgAmount;
//
//  for (int x = 0 ; x < 500 ; x++)
//    Serial.println(baseValue);
//
//   
// setupHeartBeat();

Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
}


  



void loop()
{
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);

  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.write((int)beatsPerMinute);
  Serial.println();
 /*----------------gy 271---------------*/
 MagnetometerRaw raw = compass.readRawAxis();
 MagnetometerScaled scaled = compass.readScaledAxis();
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
 Serial.print("X: ");
 Serial.print(xDegrees);
 Serial.print(",\tY:");
 Serial.print(yDegrees);
 Serial.print(",\tZ:");
 Serial.print(zDegrees);
 Serial.println(";");
 delay(100);
 
}
