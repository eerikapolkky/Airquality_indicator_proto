#include "DisplayFunctions.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern bool fan_status;
extern float temperature;

void drawNormalView(Adafruit_SSD1306 &display, float temperature, float humidity, float humidex, float avgCO2, int co2) {
  display.setTextColor(WHITE);

  // Ei tyhjennetä koko näyttöä, vaan vain muutamme tekstejä
  display.fillRect(0, 0, 128, 16, BLACK);  // Ylärivi (Temp)
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Temp:");
  if (!isnan(temperature)) {
    display.print(temperature, 1);
    display.print("C");
  } else {
    display.print("N/A");
  }

  display.fillRect(0, 16, 128, 16, BLACK);  // Keskimmäinen rivi (Hum)
  display.setCursor(0, 16);
  display.print("Hum:");
  if (!isnan(humidity)) {
    display.print(humidity, 1);
    display.print("%");
  } else {
    display.print("N/A");
  }

  display.fillRect(0, 32, 128, 32, BLACK);  // Alarivi (AvgCO2)
  display.setTextSize(1);
  display.setCursor(0, 32);
  display.print("AvgCO2:");

  display.setTextSize(2);
  display.setCursor(0, 48);
  if (avgCO2 > 0) {
    display.print(avgCO2, 0);
    display.print("ppm");
  } else {
    display.print(co2, 0);  // Näytetään suoraan sensorilta tuleva co2
    display.print("ppm");
  }

  display.display();  // Lähetetään kaikki näytölle kerralla
}
