#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"
#include "Adafruit_ImageReader.h"
#include "DRV8835MotorShield.h"

#define RA8875_INT А2
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


#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
int pin         =  7; // On Trinket or Gemma, suggest changing this to 1
int numPixels   = 7; // Popular NeoPixel ring size
int pixelFormat = NEO_GRB + NEO_KHZ800;
Adafruit_NeoPixel *pixels;
#define DELAYVAL 500 // Time (in milliseconds) to pause between pixels

Adafruit_GFX_Button buttons[2];

//Adafruit_ImageReader reader; // Class w/image-reading functions
DRV8835MotorShield motors;



//Adafruit_Image img;
//ImageReturnCode stat;
//stat = reader.loadBMP("/smileface.bmp", img);

String readString = "";

void software_Reset() // Restarts program from beginning but does not reset the peripherals and registers
{
asm volatile ("  jmp 0");  
} 
void setup() 
{
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  pixels = new Adafruit_NeoPixel(numPixels, pin, pixelFormat);
  pixels->begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
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


  tft.drawChar(240, 400, 'P', CHARCOL, CHARBACK, 2);
  tft.drawChar(260, 400, 'L', CHARCOL, CHARBACK, 2);
  tft.drawChar(280, 400, 'E', CHARCOL, CHARBACK, 2);
  tft.drawChar(300, 400, 'A', CHARCOL, CHARBACK, 2);
  tft.drawChar(320, 400, 'S', CHARCOL, CHARBACK, 2);
  tft.drawChar(340, 400, 'E', CHARCOL, CHARBACK, 2);
  tft.drawChar(380, 400, 'C', CHARCOL, CHARBACK, 2);
  tft.drawChar(400, 400, 'H', CHARCOL, CHARBACK, 2);   
  tft.drawChar(420, 400, 'O', CHARCOL, CHARBACK, 2);   
  tft.drawChar(440, 400, 'O', CHARCOL, CHARBACK, 2);  
  tft.drawChar(460, 400, 'S', CHARCOL, CHARBACK, 2);   
  tft.drawChar(480, 400, 'E', CHARCOL, CHARBACK, 2); 
  
 

      
   btn1.initButton(&tft, 550, 200, 100, 100, RA8875_GREEN, RA8875_BLUE, RA8875_WHITE, "btn1", 1);

   
    
   btn2.initButton(&tft, 200, 200, 100, 100, RA8875_GREEN, RA8875_BLUE, RA8875_WHITE, "btn2", 2);



   
     
   btn1.drawButton(false);         //Draw Button 1 on screen
   btn2.drawButton(false);        //Draw Button 2 on screen




    
   
  
    Serial.print("Status: "); Serial.println(tft.readStatus(), HEX);
    Serial.println("Waiting for touch events ...");
  
 // ImageReturnCode stat;
//  stat = reader.drawBMP("purple.bmp", tft, 0, 0);


   // const char *mychar = "1234";

}
    
void loop() {


    int Xposn, Yposn;               
    
    
    if (tft.touched()) {          //Verify the touched are
      
      tft.touchRead(&tx, &ty);  //Read the x and y value of touched area
    
     if (tx > 280 && tx < 300 && ty > 430 && ty < 500){
           pixels->clear(); // Set all pixel colors to 'off'
        
          // The first NeoPixel in a strand is #0, second is 1, all the way up
          // to the count of pixels minus one.
          for(int i=0; i<numPixels; i++) { // For each pixel...
        
            // pixels->Color() takes RGB values, from 0,0,0 up to 255,255,255
            // Here we're using a moderately bright green color:
            pixels->setPixelColor(i, pixels->Color(0, 150, 0));
        
            pixels->show();   // Send the updated pixel colors to the hardware.
        
            delay(DELAYVAL); // Pause before next pass through loop
          }
         Serial.print(tx); Serial.print(", "); Serial.println(ty); Serial.println("You are touching botton 1 ");
           
         btn2.drawButton(); //Draw bnt 2
         delay(100); 
            btn1.drawButton(); 
           btn1.drawButton(false);         //Draw Button 1 on screen
           btn2.drawButton(false);        //Draw Button 2 on screen
            //delay(100);   
      //     void fillScreen(uint16_t loop);


            // run M1 motor with positive speed
  
  
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
  software_Reset() ;                  
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
           btn1.drawButton(false);         //Draw Button 1 on screen
           btn2.drawButton(false);        //Draw Button 2 on screen
            //delay(100);       
            pixels->clear(); // Set all pixel colors to 'off'
          
            // The first NeoPixel in a strand is #0, second is 1, all the way up
            // to the count of pixels minus one.
            for(int i=0; i<numPixels; i++) { // For each pixel...
          
              // pixels->Color() takes RGB values, from 0,0,0 up to 255,255,255
              // Here we're using a moderately bright green color:
              pixels->setPixelColor(i, pixels->Color(0, 150, 0));
          
              pixels->show();   // Send the updated pixel colors to the hardware.
          
              delay(DELAYVAL); // Pause before next pass through loop
            }

//           void fillScreen(uint16_t loop);
           
// run M2 motor with positive speed
  
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  
  // run M2 motor with negative speed
  
  
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  software_Reset() ;
            
          }
     
       }  
}
