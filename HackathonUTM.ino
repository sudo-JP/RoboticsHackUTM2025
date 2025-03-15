#include <Adafruit_AHTX0.h>
#include "NewPing.h"

// include TFT and SPI libraries
#include <TFT.h>  
#include <SPI.h>

// pin definition for Arduino UNO
#define cs   10
#define dc   9
#define rst  8
#define MAX_DISTANCE 80

int analogPin = A0; //connect water sensor to analog interface 0
const int waterSensorPin = 0;
const int ledPin = 2;
const int buzzer = 6; 
const int trigPin = 5; // define ultrasonic signal receiver pin ECHO to D4 
const int echoPin = 4; 

// Create an instance of the AHT10 sensor
Adafruit_AHTX0 aht;
TFT screen = TFT(cs, dc, rst);

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

void setup() {
  Serial.begin(9600);
  Serial.println("AHT10 test");
  pinMode(ledPin, OUTPUT); 
  pinMode(buzzer, OUTPUT); 
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 

  digitalWrite(ledPin, LOW);
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

void detectObject() {
    if (sonar.ping_cm() <= 20) {
      // BUZ
        screen.text("ANIMAL DETECTED", 0, 30); 
        for(int i=0;i<80*10;i++)// output a frequency sound
{ digitalWrite(buzzer,HIGH);// sound
delay(1);//delay1ms 
digitalWrite(buzzer,LOW);//not sound
delay(1);//ms delay 
    //not sound
  }
    }
}

void loop() {
  int sensorValue = analogRead(waterSensorPin);
  
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
  dtostrf(humidity.relative_humidity, 4, 2, strtemp2);

  sprintf(num_humid,"Humidity: %s", strtemp2);
  screen.text(num_humid, 0, 10); 


  if (sensorValue > 500) {
    // High water level: Turn on the LED
    digitalWrite(ledPin, HIGH);
    screen.text("STOP WATERING YOUR PLANT", 0, 20); 
  } else if (sensorValue > 300) {
    // Medium water level: Turn on the LED
    digitalWrite(ledPin, HIGH);
    screen.text("YOUR PLANT IS GOOD", 0, 20); 
    
  } else {
    // Low or no water: Turn off the LED
    digitalWrite(ledPin, LOW);
    screen.text("WATER YOUR PLANT", 0, 20); 
  }
  detectObject(); 


  delay(5000); // Wait 5 second before the next reading
  
  screen.fillScreen(0);
  
}
