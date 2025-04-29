#include "dataStorage.h"
#include <Arduino.h>

DataStorage::DataStorage(unsigned long interval, int maxDataPoints, int startAddress)
  : _interval(interval), _maxDataPoints(maxDataPoints), _startAddress(startAddress), _currentIndex(0), _sum(0), _count(0), _hasData(false) {
  _lastUpdate = millis();
}

void DataStorage::begin() {
  _lastUpdate = millis() - _interval; // Sallitaan heti tallennus
  _currentIndex = 0;
  _sum = 0;
  _count = 0;
  _hasData = false;
}

void DataStorage::update(float co2Value) {
  if (co2Value < 0 || co2Value > 10000) return;

  _sum += co2Value;
  _count++;

  if (millis() - _lastUpdate >= _interval) {
    if (_count == 0) return;

    float avg = _sum / _count;

    Serial.print("Tallennetaan EEPROMiin keskiarvo: ");
    Serial.println(avg);

    eeprom_update_block(&avg, &eeprom_co2_data[_currentIndex], sizeof(float));

    _currentIndex = (_currentIndex + 1) % _maxDataPoints;
    _lastUpdate = millis();
    _sum = 0;
    _count = 0;
    _hasData = true;
  }
}

bool DataStorage::hasData() const {
  return _hasData;
}

void DataStorage::getAllData(float data[]) {
  for (int i = 0; i < _maxDataPoints; i++) {
    eeprom_read_block(&data[i], &eeprom_co2_data[i], sizeof(float));
  }
}

int DataStorage::getMaxDataPoints() const {
  return _maxDataPoints;
}

float DataStorage::calculateAverageFromEEPROM() {
  float data[_maxDataPoints];
  getAllData(data);

  float sum = 0;
  int count = 0;
  for (int i = 0; i < _maxDataPoints; i++) {
    if (data[i] > 0 && data[i] < 10000) {
      sum += data[i];
      count++;
    }
  }
  if (count == 0) return 0;
  return sum / count;
}
