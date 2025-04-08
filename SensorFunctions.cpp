#include "SensorFunctions.h"
#include <DHT.h>
#include <Adafruit_CCS811.h>

// Pääohjelmassa on jo alustettu DHT- ja CCS811-oliot
extern DHT dht;
extern Adafruit_CCS811 ccs;

void updateDHT(float *humidity, float *temperature) {
  *humidity = dht.readHumidity();
  *temperature = dht.readTemperature();
  // Lisää tarvittaessa virhetarkistukset
}

void updateCO2(int *co2) {
  if (ccs.available()) {
    if (!ccs.readData()) {
      *co2 = ccs.geteCO2();
    } else {
      Serial.println("Error reading CCS811 data");
    }
  }
}
