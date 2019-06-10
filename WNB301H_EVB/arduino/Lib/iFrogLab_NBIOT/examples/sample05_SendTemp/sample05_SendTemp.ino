
// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);


/*
  iFrogLab_NBIOT.h - Test library for ifroglab NB-IOT - implementation
  Copyright (c) 2019 Powen Ko, iFroglab.com All right reserved.

  
*/ 
#include <iFrogLab_NBIOT.h>

int counter=0;
iFrogLab_NBIOT NBIOT(10,11);  // RX, TX

void setup()  {
  Serial.begin(9600);


  
  

  ///////////////////////////
  Serial.println(F("DHTxx test!"));
  dht.begin();
  ///////////////////////////讀取溫度
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
  ///////////////////////////
  
  String str3=NBIOT.StringToHexString("This is my string"); 
  Serial.println(str3);
  
  // SendString
  // Send information to the telecommunications provider
  // 送資料到電信商
  String IPAddress1="211.77.241.100";
  IPAddress1="54.180.152.89";
  String str2=NBIOT.SendString(IPAddress1,20001,"This is my string","EasTone");  //EasTone(遠傳)
  //String str2=NBIOT.SendString(IPAddress1,str1,"Taiwan Mobile");  //Taiwan Mobile(台灣大哥大)

  Serial.println("================");  
  Serial.println(str2);

}

void loop() { // run over and over
  if (NBIOT.mySerial->available()) {
    Serial.write(NBIOT.mySerial->read());
  }
  if (Serial.available()) {
    NBIOT.mySerial->write(Serial.read());
  }
}
