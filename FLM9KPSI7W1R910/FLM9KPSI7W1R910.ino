/*=========================================================
Infra-Red calibration: Send mean integer value to serial
Written By Tiago A. on 21 Mar 2015
===========================================================
How to connect the sensor to the Arduino: 
  sensor - arduino
     vcc - 5V
     Gnd - gnd
     out - A0
     EN  - Do not connect

Briefing:  
This program has the sole purpose of calibrating the Infra-Red sensor.
It calculates the mean of 500 values in order to converge them into one correct value.
I am using this technique to null down the outlier values.

How to use:
After uploading this program the Arduino will start to send the mean value of the distance through the serial port.
Don't forget to open the Serial Monitor in the Tools tab. (Ctrl + Shift + M)
After 500 readings are made, a "RESET" string will be printed as well as the LED will blink, 
this is to allow the user to know when to move the sensor to another distance.


*/
long sensorsum = 0;
int n = 1;
int mean = 0;
int lastmean = 0;

// The setup routine runs once when you press reset:
void setup() {
  // Sets pin 13 for output in order to blink the LED:
  pinMode(13, OUTPUT);
  // Initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// The loop routine runs over and over again forever:
void loop() {
  
  // Read the input on analog pin 0:
  int sensorValue = analogRead(A0);
 
  // Calculate mean of measures of a specified distance in order to smooth the results and after create the regression line for distance
  sensorsum = (sensorsum + sensorValue);
  mean = (sensorsum / n);
  n = n + 1;
  
  if (n > 500) {
    digitalWrite(13, HIGH);
    delay(250);
    digitalWrite(13, LOW);
    Serial.println("-----RESET--------------------------------------------------------------------------------");
    n = 1;
    sensorsum = 0;
    lastmean = mean;
  }
  
  // The "Mean" value will vary  the whole loop beacuse it isalways calculating the mean with the read values
  // The "Last Mean" value will only show the calculated mean value just to ease the reading of the calculated value
  Serial.print(" Mean = ");
  Serial.print(mean);
  Serial.print(" Last Mean = ");
  Serial.println(lastmean);
  delay(25);
}
