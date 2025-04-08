#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include <Adafruit_ST7735.h>

// Näyttöön liittyvien funktioiden julistukset
void drawNormalView(Adafruit_ST7735 &tft, float temperature, float humidity, float humidex);
void drawHeatWarningView(Adafruit_ST7735 &tft);
void temperatureToLCD(Adafruit_ST7735 &tft, float temperature, unsigned char text_position);
void humidityToLCD(Adafruit_ST7735 &tft, float humidity, unsigned char text_position);
void co2ToLCD(Adafruit_ST7735 &tft, int co2, unsigned char text_position);

#endif
