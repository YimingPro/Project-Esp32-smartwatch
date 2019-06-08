
#include <NTPtimeESP32.h>
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'

// Initialize the OLED display using Wire library
SSD1306  display(0x3c, 5, 4);

NTPtime NTPch("ch.pool.ntp.org");   // Choose server pool as required
char *ssid      = "Iphone (Arseniy)";               // Set you WiFi SSID
char *password  = "NeverNo!";               // Set you WiFi password


strDateTime dateTime;

void setup() {
  display.init();
  display.flipScreenVertically();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);
  Serial.begin(115200);
  Serial.println();
  //********************
  display.display();
  display.clear();
  display.drawString(64, 20, String("Booted"));
  delay(2000);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 20, String("Connecting to Wi-Fi") );
  delay(2000);
 
  display.display();
  Serial.println("Booted");
  Serial.println("Connecting to Wi-Fi");

  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
}

void loop() {

  // first parameter: Time zone in floating point (for India); second parameter: 1 for European summer time; 2 for US daylight saving time (contributed by viewwer, not tested by me)
  dateTime = NTPch.getNTPtime(-5.0, 2); //CURRENTLY SET FOR US EST
  
  // check dateTime.valid before using the returned time
  // Use "setSendInterval" or "setRecvTimeout" if required
  if(dateTime.valid){
    NTPch.printDateTime(dateTime);

    byte actualHour = dateTime.hour;
    byte actualMinute = dateTime.minute;
    byte actualsecond = dateTime.second;
    int actualyear = dateTime.year;
    byte actualMonth = dateTime.month;
    byte actualday =dateTime.day;
    byte actualdayofWeek = dateTime.dayofWeek;
    String ts = String(dateTime.hour+6) + ":" + String(actualMinute / 10) + String(actualMinute % 10);

display.clear();
  Serial.print(actualHour);
display.setFont(ArialMT_Plain_24);
  display.drawString(64, 20, String(ts));
 
  display.display();

  delay(10);

    
  }
}
