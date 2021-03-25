/*
 * thermofan.h
 *
 * Created: 07.02.2021 2:34:45
 *  Author: Neb Konstantin Viktorovich
 */


#ifndef THERMOFAN_H_
#define THERMOFAN_H_

#include <avr/io.h>

class ThermoFan{
  private:
  public:
    ThermoFan();
    uint8_t fan;
    uint16_t setTemp;
    uint16_t currentTemp;
};


#endif /* THERMOFAN_H_ */