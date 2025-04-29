#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Adafruit_SSD1306.h>

void drawNormalView(Adafruit_SSD1306 &display, float temperature, float humidity, float humidex, float avgCO2, int co2);  // Lisää co2

#endif
