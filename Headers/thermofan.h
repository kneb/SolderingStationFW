/*
 * thermofan.h
 *
 * Created: 07.02.2021 2:34:45
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef THERMOFAN_H_
#define THERMOFAN_H_

#include <avr/io.h>

#define MAX_TFAN_TEMP 450
#define MIN_TFAN_TEMP 50

#define TF_HEAT_OFF 0
#define TF_HEAT_ON 1
#define TF_ON_HOLDER 2

#define PORT_GERKON PINC
#define GERKON (1 << PINC3)

class ThermoFan{
  private:
  public:
    ThermoFan();
    uint8_t fan;
    uint8_t fanBuf;
    uint16_t temp;
    uint16_t currentTemp;
    uint8_t isPowered;
    void setPowerOn();
    void setPowerOff();
    void setPowerSleep();
    void setFan(uint8_t fan);
    void setFan(bool isClockwise);
    void setTemp(uint16_t temp);
    void setTemp(bool isClockwise);
    void getStatus();
};


#endif /* THERMOFAN_H_ */