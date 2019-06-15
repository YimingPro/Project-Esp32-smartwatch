#include "AdafruitIO_WiFi.h"
 
#define WIFI_SSID       "174-2.4"
#define WIFI_PASS       "mzenvQswr3Yy"
 
#define IO_USERNAME    "LuciferCoder01"
#define IO_KEY         "3ef67556faea4d279b87ef2b38576bbe"
 
// Connect to Wi-Fi and Adafruit IO handel 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
 
// Create a feed object that allows us to send data to
AdafruitIO_Feed *temperatureFeed = io.feed("WatchData");
 
 
void setup() 
{
  // Enable the serial port so we can see updates
  Serial.begin(115200);
 
  // Connect to Adafruit IO
  io.connect();
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
}
 
void loop() 
{
  // Always keep this at the top of your main loop
  // While not confirmed, this implies that the Adafruit IO library is not event-driven
  // This means you should refrain from using infinite loops
  io.run();
 
  // Send 10 to our Workshop Temperature Feed
  temperatureFeed->save("test");
 
  // This is so we can see some response on the computer
  Serial.print("Data sent");
 
  // DONT SEND A BILLION DATA POINTS! This slows down the program so that it sends readings once every 5 seconds
  delay(5000);
}
