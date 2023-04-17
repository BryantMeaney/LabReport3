//The purpose of this lab was to become familar with the ultra sonic sensor, 
// with this sensor we will measure and then calulate distance.
// with this we utilized a library for the ultrasonic sensor 
// further familiarizing us with the functions of librarys. 
#include <afstandssensor.h>
#include <LiquidCrystal.h>
// Assigning pins to the LCD Display
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// defines pins numbers
const int trigPin = 6;
const int echoPin = 5;
// defines variables
//Variable used in the equation for distanc e
long duration;
float distance;
void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication
   lcd.begin(16, 2);
}
void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(duration);
  //LCD print the distance in CM  to the LCD Monitor 
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(distance);
  lcd.print("CM");
  delay(200);
}