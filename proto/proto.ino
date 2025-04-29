#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <Adafruit_CCS811.h>

#include "SensorFunctions.h"
#include "DisplayFunctions.h"
#include "dataStorage.h"
#include "EEPROMStorage.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// DHT11 asetukset
#define DHTPIN 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_CCS811 ccs;

// Tuuletin ohjaus PB1
#define FAN_PIN_PORT PORTB
#define FAN_PIN_DDR  DDRB
#define FAN_PIN_BIT  PB1

// Sensorimuuttujat
float humidity = 0;
float temperature = 0;
int co2 = 0;
unsigned long previousMillis = 0;  // Muuttuja ajan seuraamiseen
const long interval = 5000;         // Päivitysväli (5 sekuntia)

// EEPROM tallennus (10 sekuntia väli testissä)
DataStorage dataStorage(10 * 1000UL, 72, 0);

void setup() {
  Serial.begin(9600);

  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  display.clearDisplay();
  display.display();

  dht.begin();

  if (!ccs.begin()) {
    Serial.println(F("Failed to start CCS811 sensor! Check wiring."));
    while (1);
  }

  while (!ccs.available()); // Odota että CCS811 valmis

  //FAN_PIN_DDR |= (1 << FAN_PIN_BIT);
  //FAN_PIN_PORT &= ~(1 << FAN_PIN_BIT); // Aluksi tuuletin pois

  dataStorage.begin();
}


void loop() {
  unsigned long currentMillis = millis();  // Haetaan nykyinen aika

  // Jos 5 sekuntia on kulunut
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Päivitetään edellinen aika

    updateDHT(&humidity, &temperature);
    updateCO2(&co2);  // Haetaan oikea CO₂ arvo sensorilta

    // Tuuletinlogiikka
   // if (temperature >= 24.0) {
      //FAN_PIN_PORT |= (1 << FAN_PIN_BIT);  // Tuuletin päälle
   // } else if (temperature <= 22.0) {
   //  FAN_PIN_PORT &= ~(1 << FAN_PIN_BIT); // Tuuletin pois
   // }

    Serial.print("CO2-lukema: ");
    Serial.println(co2);

    dataStorage.update(co2);  // Tallennetaan co2 EEPROMiin

    float avgCO2 = dataStorage.calculateAverageFromEEPROM();
    drawNormalView(display, temperature, humidity, 0, avgCO2, co2);  // Lisää co2 myös argumenttina
  }
}
