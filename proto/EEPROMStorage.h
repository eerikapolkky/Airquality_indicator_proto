#ifndef EEPROMSTORAGE_H
#define EEPROMSTORAGE_H

#include <avr/eeprom.h>

extern uint16_t EEMEM eeprom_signature;
extern float EEMEM eeprom_co2_data[72]; // Tallennetaan CO2-arvot!
void clearEEPROM();


#endif
