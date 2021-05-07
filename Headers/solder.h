/*
 * solder.h
 *
 * Created: 07.02.2021 2:33:41
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef SOLDER_H_
#define SOLDER_H_

#include <avr/io.h>

#define MAX_SOLDER_TEMP 410
#define MIN_SOLDER_TEMP 50

#define SOL_HEAT_OFF 0
#define SOL_HEAT_ON 1
#define SOL_HEAT_SLEEP 2

#define PORT_VIBRO PIND
#define VIBRO (1 << PIND3)

class Solder{
  private:
    
  public:
    Solder();
    uint16_t temp;
    uint16_t currentTemp;
    uint8_t isPowered;
    void setPowerOn();
    void setPowerOff();
    void setTemp(uint16_t temp);
    void setTemp(bool isClockwise);
};

#endif /* SOLDER_H_ */