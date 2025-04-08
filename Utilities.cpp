#include "Utilities.h"
#include <math.h>
#include <Adafruit_ST7735.h>

// Ulkoisia globaaleja muuttujia (määritelty pääohjelmassa)
extern String message;
extern int text_color_humidex;

float calculateHumidex(float temperature, float humidity) {
  float e;
  e = (6.112 * pow(10, (7.5 * temperature / (237.7 + temperature))) * humidity / 100);
  float humidex = temperature + 0.55555555 * (e - 10.0);
  return humidex;
}

uint16_t Color565(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

void fixNumberPosition(Adafruit_ST7735 &tft, float number) {
  if ((number >= -40) && (number < -9.9)) { }
  if ((number >= -9.9) && (number < 0.0)) { tft.print(" "); }
  if ((number >= 0.0) && (number < 9.9)) { tft.print(" "); }
  if ((number >= 9.9) && (number < 99.9)) { tft.print(" "); }
  if ((number >= 99.9) && (number < 151)) { tft.print(""); }
}
