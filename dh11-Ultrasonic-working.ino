#include <DHT.h>
#include <LiquidCrystal.h>
#define DHTPIN 2      // the DHT11 data pin
#define DHTTYPE DHT11 // the DHT11 sensor type
DHT dht(DHTPIN, DHTTYPE);

#define trigPin 6    
#define echoPin 5    
#define maxDistance 100 

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // measure distance using HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.034 / 2;

 
    // calculate the compensated distance based on temperature and humidity
    float compensatedDistance = distance / (1 + 0.00016 * temperature + 0.00039 * humidity);

    Serial.print("Distance (cm): ");
    Serial.print(compensatedDistance);
    Serial.print(", Temperature (C): ");
    Serial.print(temperature);
    Serial.print(", Humidity (%): ");
    Serial.println(humidity);
  lcd.setCursor(0, 0);
  lcd.print("Distance: ");
  lcd.print(compensatedDistance);
  lcd.print("CM");
  delay(500);
  }

  
  
