#include "SensorFunctions.h"
#include <DHT.h>
#include <Arduino.h>
#include <Adafruit_CCS811.h>

extern DHT dht;
extern Adafruit_CCS811 ccs;
extern float humidity;
extern float temperature;


void updateDHT(float *humidityPtr, float *temperaturePtr) {
  int tries = 5;
  while (tries--) {
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    if (!isnan(h) && !isnan(t)) {
      *humidityPtr = h;
      *temperaturePtr = t;
      return;
    }
    delay(1000); // odota 1 sekunti ja yritä uudelleen
  }
  Serial.println("DHT reading failed after retries.");
}

void updateCO2(int *co2Ptr) {
  if (ccs.available()) {
    if (!ccs.readData()) {
      *co2Ptr = ccs.geteCO2();
    } else {
      *co2Ptr = 0;
    }
  } else {
    *co2Ptr = 0;
  }
}
