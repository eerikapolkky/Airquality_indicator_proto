#ifndef UTILITIES_H
#define UTILITIES_H

#include <Adafruit_ST7735.h>

float calculateHumidex(float temperature, float humidity);
uint16_t Color565(uint8_t r, uint8_t g, uint8_t b);
void fixNumberPosition(Adafruit_ST7735 &tft, float number);

#endif
