// The goal of this lab activity was to utilize two libraries together to better calculate 
//the distance measurment of the ultrasonic sensor, these skills transfer 
// to other libraries and other functions that we may want to combine. 

#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 2      // the DHT11 data pin
#define DHTTYPE DHT11 // the DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);
//define the Trig pin
#define trigPin 6    
//Define the echo pin
#define echoPin 5    
#define maxDistance 100 
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  Serial.begin(9600);
  //Setting the pinmodes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //setting up the LCD
  dht.begin();
  lcd.begin(16, 2);
}
void loop() {
  //Creating the variables from the DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // measure distance using HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //Variables for the Ultrasonic 
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;
// calculate the compensated distance based on temperature and humidity
    float compensatedDistance = distance / (1 + 0.00016 * temperature + 0.00039 * humidity);
    //serial print the distance 
    Serial.print("Distance (cm): ");
    Serial.print(compensatedDistance);
    //serial print the temprature in C
    Serial.print(", Temperature (C): ");
    Serial.print(temperature);
    //serial print the humdity 
    Serial.print(", Humidity (%): ");
    Serial.println(humidity);
    //set the LCD
  lcd.setCursor(0, 0);
  //Display the distance on the LCD
  lcd.print("Distance: ");
  lcd.print(compensatedDistance);
  lcd.print("CM");
  delay(500);
  }
