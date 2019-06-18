
#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

#include "AdafruitIO_WiFi.h"

#include <NTPtimeESP32.h>
//#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"'
#include "SH1106.h" 
// Initialize the OLED display using Wire library
SH1106  display(0x3c, 17, 16);

NTPtime NTPch("ch.pool.ntp.org");   // Choose server pool as required
char *ssid      = "Iphone (Arseniy)";               // Set you WiFi SSID
char *password  = "NeverNo!";               // Set you WiFi password

strDateTime dateTime;

 
#define WIFI_SSID       "Iphone (Arseniy)"
#define WIFI_PASS       "NeverNo!"
 
#define IO_USERNAME    "LuciferCoder01"
#define IO_KEY         "3ef67556faea4d279b87ef2b38576bbe"
// Connect to Wi-Fi and Adafruit IO handel 
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
 
// Create a feed object that allows us to send data to
AdafruitIO_Feed *temperatureFeed = io.feed("WatchData");
 


SoftwareSerial mySerial(10, 11); // RX, TX
char mystr[50];

String gyroValue;
String gyroPrevValue = "";

bool watchState = true;

#define BUZZER 32
#define FLASHLIGHT 27
#define BUTTON_ON 22
#define BUTTON_OFF 23
#define BUTTON_LEFT    5                          
#define BUTTON_RIGHT   19     
#define PIXEL_PIN    33    // Digital IO pin connected to the NeoPixels.  
#define PIXEL_COUNT 1


// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  display.init();
  display.flipScreenVertically();
  display.setColor(WHITE);
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_24);

  display.display();
  display.clear();
  display.drawString(64, 20, String("Booted"));
  delay(2000);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(64, 20, String("Connecting") );
  delay(2000);

  display.display();
  Serial.println("Booted");
  Serial.println("Connecting");

  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // Connect to Adafruit IO
  io.connect();
  // wait for a connection
  while(io.status() < AIO_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  // set the data rate for the SoftwareSerial port

    pinMode(BUTTON_LEFT, INPUT_PULLUP);
    pinMode(BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(BUTTON_ON, INPUT_PULLUP);
    pinMode(BUTTON_OFF, INPUT_PULLUP);
    pinMode(BUZZER,OUTPUT);
    pinMode(FLASHLIGHT,OUTPUT);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'

}

void adafruitPost(String heartbeat){
  // Always keep this at the top of your main loop
  // While not confirmed, this implies that the Adafruit IO library is not event-driven
  // This means you should refrain from using infinite loops
  io.run();
 
  // Send 10 to our Workshop Temperature Feed
  temperatureFeed->save(heartbeat);
 
  // This is so we can see some response on the computer
  Serial.print("Data sent");
 
  // DONT SEND A BILLION DATA POINTS! This slows down the program so that it sends readings once every 5 seconds
  delay(5000);
  }

void timeFunction() {

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

void soundone(){
    unsigned char i,j;

  for(i=0;i<5;i++)

  {

    for(i=0;i<200;i++)

    {

      digitalWrite(BUZZER,HIGH);

      delay(1);//Change this could adjust voice

      digitalWrite(BUZZER,LOW);

      delay(1);

    }

    for(i=0;i<100;i++)

    {
      digitalWrite(BUZZER,HIGH);

      delay(2);

      digitalWrite(BUZZER,LOW);

      delay(2);
    }
  }

}

void gyro(){
  if(abs(abs(gyroValue.toInt())-abs(gyroPrevValue.toInt())) >= 300){
    Serial.println("Fall down");
    
    colorWipe(strip.Color(255, 0, 0), 50); 
    soundone();
    
    gyroPrevValue = gyroValue;
    
    }
  }

void soundtwo(){
    unsigned char i,j;

  for(i=0;i<5;i++)

  {

    for(i=0;i<100;i++)

    {

      digitalWrite(BUZZER,HIGH);

      delay(2);//Change this could adjust voice

      digitalWrite(BUZZER,LOW);

      delay(2);

    }

    for(i=0;i<200;i++)

    {
      digitalWrite(BUZZER,HIGH);

      delay(1);

      digitalWrite(BUZZER,LOW);

      delay(1);
    }
  }}

void showHeart(String heartValue){
  display.clear();
  display.setFont(ArialMT_Plain_24);
  String myData = "Pulse: "+heartValue;
  display.drawString(64, 20, myData);
 
  display.display();

  delay(10);
  }

  // Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void loop() { // run over and over
colorWipe(strip.Color(0, 0, 0), 50); 
if(digitalRead(BUTTON_ON)==LOW)
  {
    digitalWrite(FLASHLIGHT,LOW);
  }
  if(digitalRead(BUTTON_OFF)==LOW)
  {
    digitalWrite(FLASHLIGHT,HIGH);
  }

  Serial.readStringUntil('\n');
  String first  = Serial.readStringUntil(',');

  if((digitalRead(BUTTON_LEFT)==LOW) || (digitalRead(BUTTON_RIGHT)==LOW))
  {
    watchState=!watchState;
    soundtwo();
    colorWipe(strip.Color(0, 0, 255), 50);
  }
  if(watchState){
    timeFunction();
    }
    else{
      showHeart(first);
      }




adafruitPost(first);
String gyroValue = Serial.readStringUntil(',');
//Serial.readStringUntil(',');


if(gyroPrevValue = "")
  gyroPrevValue = gyroValue;

gyro();

Serial.readBytes(mystr,50);
//mystr = Serial.readString();
Serial.println(first);
Serial.println(mystr);

}
