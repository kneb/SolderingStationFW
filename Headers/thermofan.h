/*
 * thermofan.h
 *
 * Created: 07.02.2021 2:34:45
 *  Author: Neb Konstantin Viktorovich
 */
#ifndef __AVR_ATmega8A__
#define __AVR_ATmega8A__
#endif

#ifndef THERMOFAN_H_
#define THERMOFAN_H_

#include <avr/io.h>

#define TF_HEAT 1
#define TF_SLEEP 2

#define GERKON (1 << PINC3)

class ThermoFan{
  private:
  public:
    ThermoFan();
    uint8_t fan;
    uint16_t setTemp;
    uint16_t currentTemp;
    uint8_t status;
};


#endif /* THERMOFAN_H_ */