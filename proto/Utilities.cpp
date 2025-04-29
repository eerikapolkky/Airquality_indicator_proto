#include "Utilities.h"
#include <math.h>
#include <Adafruit_SSD1306.h>

extern String message;

float calculateHumidex(float temperature, float humidity) {
  float e;
  e = (6.112 * pow(10, (7.5 * temperature / (237.7 + temperature))) * humidity / 100);
  float humidex = temperature + 0.55555555 * (e - 10.0);
  return humidex;
}

void fixNumberPosition(Adafruit_SSD1306 &display, float number) {
  // OLED ei tarvitse väkisin tyhjää tilaa mutta voit säätää myöhemmin jos haluat
}
