#include <Adafruit_AHTX0.h>

// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8
int analogPin = 0; //connect water sensor to analog interface 0
int water = 0; //define the initial value of variable ‘data’ as 0
const int led = 0;

// Create an instance of the AHT10 sensor
Adafruit_AHTX0 aht;
TFT screen = TFT(cs, dc, rst);

void setup() {
  Serial.begin(9600);
  Serial.println("AHT10 test");
  pinMode(led, OUTPUT); 
  // Initialize the sensor
  if (!aht.begin()) {
    Serial.println("Could not find AHT10 sensor! Check wiring.");
    while (1);
  }
  Serial.println("AHT10 found!");

  screen.begin(); 
  screen.background(0, 0, 0); 
  screen.setTextSize(1); 
  screen.stroke(255,255,255);

}

void loop() {
  water = analogRead(analogPin); 
  
  // Read temperature and humidity
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp); // Populate temp and humidity objects with data

  // Print the results
  char num_temp[100];
  char strtemp1[64]; 
  // Temperature
  dtostrf(temp.temperature, 4, 2, strtemp1);

  sprintf(num_temp,"Temperature: %s C", strtemp1);
  screen.text(num_temp, 0, 0); 

  // Humidity
  char num_humid[100];
  char strtemp2[64];
  dtostrf(humidity.relative_humidity, 4, 2, strtemp);

  sprintf(num,"Temperature: %s C", strtemp);
  screen.text(num, 0, 0); 


  // Water
  if (water > 700) {
    digitalWrite(led, HIGH); 
  }
  else {
    digitalWrite(led, LOW); 
  }
  // Serial.print("Temperature: "); 
  // Serial.print(temp.temperature); 
  // Serial.println(" °C");

  // Serial.print("Humidity: "); 
  // Serial.print(humidity.relative_humidity); 
  // Serial.println(" %");

  delay(5000); // Wait 1 second before the next reading
  
  //screen.fill(0,0,0);
  //screen.rect(-20, -20, 1000, 10000);
  screen.fillScreen(0);
  
  
}