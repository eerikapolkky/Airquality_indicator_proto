#include <avr/eeprom.h>

uint16_t EEMEM eeprom_signature = 0x1234;
float EEMEM eeprom_co2_data[72] = {0}; // CO2 data taulukko

void clearEEPROM() {
  for (int i = 0; i < 72; i++) {
    float zero = 0.0;
    eeprom_update_block(&zero, &eeprom_co2_data[i], sizeof(float));
  }
}