// The goal of this code was to become familiar with the function of multiple refreshing 
// screens controlled by a momentary push button.
//With this we also continued to cbecome more effiecent with both the DHT11 amd Libraries


// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <afstandssensor.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <LiquidCrystal.h>
#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);
AfstandsSensor afstandssensor(6, 5);  

uint32_t delayMS;


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
// create our custom character 
byte customChar[8] = {
	0b01100,
	0b10010,
	0b10010,
	0b01100,
	0b00000,
	0b00000,
	0b00000,
	0b00000
};
//write the variables for the push button 
int PBState = LOW;
int lastButtonState;
int currentButtonState;


void setup() {
lcd.createChar(0,customChar);
  Serial.begin(9600);
  // Initialize device.
  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
pinMode(3, INPUT_PULLUP);
currentButtonState = digitalRead(3);
}

void loop() {
  // creates the varible to hold the count of what screen we are on 
lastButtonState    = currentButtonState;      // save the last state
currentButtonState = digitalRead(3);
  // Get temperature event and print its value.
if(lastButtonState == 1 && currentButtonState == 0) {
// every time the button is pushed increace PBState by 1 
    PBState = PBState + 1;
if (PBState>2){
  // restart the counter everytime is goes above 2 
  PBState = 0;
}

  }

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  float temp = event.temperature;
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.print(F("°C"));
    Serial.print(F("\t"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.print(F("%"));
    Serial.print(F("\t"));
  }
Serial.println(PBState);
  lcd.setCursor(0, 0);
if (PBState == 0){
  //if the push button has not yet been pressed then the LCD will clear and then display the humidity 
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Humidity ");
lcd.print(event.relative_humidity);
lcd.print("%");
}
if (PBState==1){
  //If the push button is pressed once the LCD will clear and display the temprature in celcius 
lcd.clear();
lcd.print("Temp: ");
lcd.print(temp);
lcd.print("C");
lcd.write(byte(0));
}
if(PBState==2){
  // If the Push button is pressed twice it will display the temprature in fehrinheit 
lcd.clear();
float tempf = ((9/5)*temp)+32;
lcd.print("Temp: ");
lcd.print(tempf);
lcd.print("F");
lcd.write(byte(0));
}


}
