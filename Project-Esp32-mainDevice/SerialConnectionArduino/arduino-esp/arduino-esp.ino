#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX
//////////////////////
#include <DRV8835MotorShield.h>


#define LED_PIN 13

DRV8835MotorShield motors;
////////////////
void setup() {
////////////////
pinMode(LED_PIN, OUTPUT);
///////////////////
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }


  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world?");
}

void motorRun(){
  digitalWrite(LED_PIN, HIGH);
  
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  digitalWrite(LED_PIN, LOW);
  delay(500);
  }

void loop() { // run over and over
  String messg;
  if (mySerial.available()) {
//      messg = mySerial.read();
//      Serial.println(messg);
      String mssgIN = mySerial.readString();
      String mssg = "Motor 1\n";
      if(mssg.equals(mssgIN))
        motorRun();
        
  }
//  if (Serial.available()) {
//    mySerial.write(Serial.read());
    
//  }
}
