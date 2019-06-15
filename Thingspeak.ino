
#include <Wire.h>
#include "MAX30105.h"
#include <HMC5883L.h>
//#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
MAX30105 particleSensor;
HMC5883L compass;
String apiKey = "KKN0UXEL3E1L0ZKR";                  //  Enter your Write API key from ThingSpeak
const char *ssid =  "Grpup2";                                    // replace with your wifi ssid and wpa2 key
const char *pass =  "12345678";
const char* server = "api.thingspeak.com";
WiFiClient client;
void setup()
{
  Serial.begin(115200);
    delay(10);
    Serial.println("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
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

int h = 0;
float t =0;

//h = hallRead();
//t = ((temprature_sens_read()-32)/1.8);                //changing temperature parameter to celsius
 if (client.connect(server,80))                                 //   "184.106.153.149" or api.thingspeak.com
    {  
                            
    String postStr = apiKey;
    postStr +="&field1=";
    postStr += String(h);
    postStr += "&field2=";
    postStr += String(t);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-KKN0UXEL3E1L0ZKR: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
 
    Serial.print("Hall: ");
    Serial.println(h);
    Serial.print("Temperature:");
    Serial.print(t);
    Serial.println(" C");
                             
    Serial.println("%. Send to Thingspeak.");
}
    client.stop();
    Serial.println("Waiting...");
    delay(10000);



  
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
