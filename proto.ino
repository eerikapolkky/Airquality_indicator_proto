#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <DHT.h>
#include <math.h>
#include <Adafruit_CCS811.h>

#include "DisplayFunctions.h"
#include "SensorFunctions.h"
#include "Utilities.h"

// Näyttö- ja anturikytkennät
#define TFT_CS 10
#define TFT_DC 9
#define TFT_RST 8
#define TFT_SCLK 13
#define TFT_MOSI 11

#define DHTPIN 7         // DHT11-anturi
#define DHTTYPE DHT11    // Käytetään DHT11-anturia

#define FAN_PIN 4        // Tuuletinohjaus (kytketty transistorin ja diodin kautta)
#define CO2_THRESHOLD 500  // CO2-raja-arvo (ppm)

DHT dht(DHTPIN, DHTTYPE);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_CCS811 ccs;  // CCS811-anturi

enum DisplayMode { NORMAL_VIEW, HEAT_WARNING_VIEW };
int currentView = NORMAL_VIEW;
unsigned long viewStartMillis = 0;

// Globaaleja mittausmuuttujia
float humidity, temperature, humidex;
int co2 = 0;
bool fan_status = false;
String message;
int text_color_humidex;

void setup() {
  Serial.begin(9600);
  
  // Alustetaan DHT11-anturi
  dht.begin();
  Serial.println("DHT Sensor (DHT11) Initialized");

  // Alustetaan CCS811-anturi
  if(!ccs.begin()){
    Serial.println("Failed to start CCS811 sensor! Tarkista kytkennät.");
    while(1);  // pysäytetään ohjelma, jos anturia ei löydy
  }
  // Anna CCS811:lle hetki alustua
  delay(100);
  Serial.println("CCS811 Sensor Initialized");

  // Asetetaan tuulettimen ohjauspinni OUTPUT-tilaan
  pinMode(FAN_PIN, OUTPUT);
  digitalWrite(FAN_PIN, LOW);

  // Alustetaan TFT-näyttö
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  
  // Näkymän vaihtamisen ajastin
  viewStartMillis = millis();
}

void loop() {
  // Päivitetään DHT-anturin lukemat
  updateDHT(&humidity, &temperature);
  humidex = calculateHumidex(temperature, humidity);

  // Luetaan CCS811:n CO2-arvot
  updateCO2(&co2);

 /* // Tuuletin päälle, jos CO2 ylittää raja-arvon, TÄTÄ EI KÄYTETÄ
  if(co2 > CO2_THRESHOLD){
    digitalWrite(FAN_PIN, HIGH);
    fan_status = false;
  }
  else {
    digitalWrite(FAN_PIN, LOW);
    fan_status = false;
  }
  */
  // Vaihdetaan näkymää, jos lämpötila on yli 25°C (30 sekunnin välein)
  if (temperature > 25) {
    if (millis() - viewStartMillis >= 3000) {
      currentView = (currentView == NORMAL_VIEW) ? HEAT_WARNING_VIEW : NORMAL_VIEW;
      viewStartMillis = millis();
      digitalWrite(FAN_PIN, HIGH);
    fan_status = true;
    }
  }
  else {
    currentView = NORMAL_VIEW;
    viewStartMillis = millis();
  }

  // Piirretään nykyinen näkymä
  if (currentView == NORMAL_VIEW) {
    drawNormalView(tft, temperature, humidity, humidex);
  }
  else if (currentView == HEAT_WARNING_VIEW) {
    drawHeatWarningView(tft);
  }

  delay(2000);
}
