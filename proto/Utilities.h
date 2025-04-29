#ifndef UTILITIES_H
#define UTILITIES_H

#include <Adafruit_SSD1306.h>

float calculateHumidex(float temperature, float humidity);
void fixNumberPosition(Adafruit_SSD1306 &display, float number);

extern Adafruit_SSD1306 display; // määritelty pääohjelmassa

#endif

