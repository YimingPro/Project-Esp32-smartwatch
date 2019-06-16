
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "Adafruit_ImageReader.h"
#include "DRV8835MotorShield.h"



#define LED_PIN 13

#define RA8875_INT 3
#define RA8875_CS 10
#define RA8875_RESET 9

#define BLACK 0x0000
#define BLUE 0x001F
#define RED 0xF800
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

#define BACKCOLOR 0x841F 
#define CHARCOL 0xFFFF
#define CHARBACK 0x0000


Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

uint16_t tx, ty;

Adafruit_GFX_Button btn1;
Adafruit_GFX_Button btn2;



Adafruit_GFX_Button buttons[2];
Adafruit_ImageReader reader; // Class w/image-reading functions
DRV8835MotorShield motors;



//Adafruit_Image img;
//ImageReturnCode stat;
//stat = reader.loadBMP("/smileface.bmp", img);


void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  Serial.println("RA8875 start");

  /* Initialise the display using 'RA8875_800x480' */
  if (!tft.begin(RA8875_800x480)) {
    Serial.println("RA8875 Not Found!");
    while (1); 
  }

  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
 
    
  //Screen backgroud
  
  tft.fillScreen(RA8875_BLACK);
  tft.touchEnable(true);

  //draw button label
  
  tft.drawChar(510, 300, 'U', CHARCOL, CHARBACK, 2);
  tft.drawChar(530, 300, 'S', CHARCOL, CHARBACK, 2);
  tft.drawChar(550, 300, 'E', CHARCOL, CHARBACK, 2);
  tft.drawChar(570, 300, 'R', CHARCOL, CHARBACK, 2);
  tft.drawChar(590, 300, '2', CHARCOL, CHARBACK, 2);
  
  tft.drawChar(160, 300, 'U', CHARCOL, CHARBACK, 2);
  tft.drawChar(180, 300, 'S', CHARCOL, CHARBACK, 2);
  tft.drawChar(200, 300, 'E', CHARCOL, CHARBACK, 2);
  tft.drawChar(220, 300, 'R', CHARCOL, CHARBACK, 2);
  tft.drawChar(240, 300, '1', CHARCOL, CHARBACK, 2);
   
  // draw clock String


  tft.drawChar(310, 400, '2', CHARCOL, CHARBACK, 2);
  tft.drawChar(330, 400, '3', CHARCOL, CHARBACK, 2);
  tft.drawChar(350, 400, ':', CHARCOL, CHARBACK, 2);
  tft.drawChar(370, 400, '5', CHARCOL, CHARBACK, 2);
  tft.drawChar(390, 400, '9', CHARCOL, CHARBACK, 2);
  tft.drawChar(410, 400, ':', CHARCOL, CHARBACK, 2);
  tft.drawChar(430, 400, '5', CHARCOL, CHARBACK, 2);
  tft.drawChar(450, 400, '9', CHARCOL, CHARBACK, 2);


      
   btn1.initButton(&tft, 550, 200, 100, 100, RA8875_GREEN, RA8875_BLUE, RA8875_WHITE, "btn1", 1);
    
   btn2.initButton(&tft, 200, 200, 100, 100, RA8875_GREEN, RA8875_BLUE, RA8875_WHITE, "btn2", 2);
     
   btn1.drawButton(false);         //Draw Button 1 on screen
   btn2.drawButton(false);        //Draw Button 2 on screen
    
   
  
    Serial.print("Status: "); Serial.println(tft.readStatus(), HEX);
    Serial.println("Waiting for touch events ...");
  
 // ImageReturnCode stat;
//  stat = reader.drawBMP("purple.bmp", tft, 0, 0);
    

}
    
void loop() {


    int Xposn, Yposn;               

    if (tft.touched()) {          //Verify the touched are
      tft.touchRead(&tx, &ty);  //Read the x and y value of touched area
    
     if (tx > 280 && tx < 300 && ty > 430 && ty < 500){

         Serial.print(tx); Serial.print(", "); Serial.println(ty); Serial.println("You are touching botton 1 ");
           
         btn2.drawButton(); //Draw bnt 2
         delay(100); 
            btn1.drawButton(); 
            //delay(100);               
        }

// run M1 motor with positive speed
  
  digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  
  // run M1 motor with negative speed
  
  digitalWrite(LED_PIN, LOW);
  
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
          
    }
 
       if (tft.touched()) {          //Verify the touched are
       tft.touchRead(&tx, &ty); //Read the x and y value of touched area
      
        if  (tx > 600 && tx < 700 && ty > 390 && ty < 500){
          
          Serial.print(tx); Serial.print(", "); Serial.println(ty); Serial.println("You are touching botton 2 ");
          Serial.print("You are touching botton 2 ");
           btn1.drawButton(); //Draw bnt 1
            delay(100); 
           btn2.drawButton(); 
            //delay(100);    
          }
     
       }  
}
