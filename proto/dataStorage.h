#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <Adafruit_SSD1306.h>
#include <avr/eeprom.h>
#include "EEPROMStorage.h"

class DataStorage {
public:
  DataStorage(unsigned long interval, int maxDataPoints, int startAddress);
  void begin();
  void update(float co2Value);
  bool hasData() const;
  void getAllData(float data[]);
  int getMaxDataPoints() const;
  float calculateAverageFromEEPROM();

private:
  unsigned long _interval;
  int _maxDataPoints;
  int _startAddress;
  int _currentIndex;
  float _sum;
  int _count;
  bool _hasData;
  unsigned long _lastUpdate;
};

#endif
