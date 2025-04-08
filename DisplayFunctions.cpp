#include "DisplayFunctions.h"
#include "Utilities.h"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Näytölle käytettävät vakiot
#define COLOR2 ST7735_BLACK

// Ulkoisia globaaleja muuttujia (määritelty pääohjelmassa)
extern bool fan_status;
extern int co2;
extern float temperature;

void drawNormalView(Adafruit_ST7735 &tft, float temperature, float humidity, float humidex) {
  tft.fillScreen(COLOR2);
  tft.drawRect(0, 0, 128, 160, ST7735_WHITE);
  tft.drawLine(0, 50, 128, 50, ST7735_WHITE);
  tft.drawLine(0, 100, 128, 100, ST7735_WHITE);
  temperatureToLCD(tft, temperature, 4);
  humidityToLCD(tft, humidity, 55);
  co2ToLCD(tft, co2, 105); // Näytetään CO₂-arvo humidexin sijaan, joka oli 1.1 protossa
}

void drawHeatWarningView(Adafruit_ST7735 &tft) {/* // EI ENÄÄ KÄYTÖSSÄ, värikoodattu
  tft.fillScreen(ST7735_RED);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.setCursor(5, 60);
  tft.print("KUUMUUUSVAROITUS!");
  tft.setTextSize(1);
  tft.setCursor(5, 100);
  //tft.print("Tarkista lämpo!");
}
*/
void temperatureToLCD(Adafruit_ST7735 &tft, float temperature, unsigned char text_position) {
  // Määritellään lämpötilalle tekstiväri
  uint16_t tempColor;
  if (temperature < 19.5) {
    tempColor = ST7735_BLUE;
  } else if (temperature >= 19.5 && temperature <= 22) {
    tempColor = ST7735_GREEN;
  } else if (temperature > 22 && temperature <= 24.5) {
    tempColor = ST7735_YELLOW;
  } else if (temperature > 25) {
    tempColor = ST7735_RED;
  } else {
    tempColor = ST7735_WHITE;
  }
  
  tft.setCursor(4, text_position);
  tft.setTextColor(ST7735_WHITE, COLOR2);
  tft.setTextWrap(true);
  tft.print("Temperature:");
  
  tft.setTextSize(3);
  tft.setCursor(1, text_position + 20);
  fixNumberPosition(tft, temperature);
  tft.setTextColor(tempColor, COLOR2);
  tft.print(temperature, 1);
  tft.setCursor(108, text_position + 20);
  tft.print("C");
  tft.drawChar(90, text_position + 20, 247, tempColor, COLOR2, 2);
}

void humidityToLCD(Adafruit_ST7735 &tft, float humidity, unsigned char text_position) {
  tft.setTextColor(ST7735_WHITE, COLOR2);
  tft.setCursor(4, text_position);
  tft.setTextSize(1);
  tft.println("Humidity:");
  tft.setTextSize(3);
  tft.setCursor(1, text_position + 20);
  fixNumberPosition(tft, humidity);
  tft.print(humidity, 1);
  tft.print(" %");
}

void co2ToLCD(Adafruit_ST7735 &tft, int co2, unsigned char text_position) {
  // Määritellään CO₂-arvolle tekstiväri
  uint16_t co2Color;
  if (co2 > 1000) {
    co2Color = ST7735_RED;
  } else if (co2 >= 800 && co2 <= 900) {
    co2Color = ST7735_YELLOW;
  } else if (co2 < 700) {
    co2Color = ST7735_GREEN;
  } else {
    co2Color = ST7735_WHITE;
  }

  tft.setCursor(4, text_position);
  tft.setTextSize(1);
  tft.println("CO2 reading:");
  
  tft.setTextSize(3);
  tft.setCursor(1, text_position + 17);
  tft.setTextColor(co2Color, COLOR2);
  tft.print(co2);
  tft.print(" ppm");
  
  // Jos tuuletin on päällä, ilmoitetaan siitä
  if (fan_status) {
    tft.setTextSize(1);
    tft.setCursor(4, text_position + 45);
    tft.println("Tuuletin aktivoitu!");
  }
}
