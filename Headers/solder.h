/*
 * solder.h
 *
 * Created: 07.02.2021 2:33:41
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef SOLDER_H_
#define SOLDER_H_

#include <avr/io.h>
#include <avr/eeprom.h>

#define MAX_SOLDER_TEMP 410
#define MIN_SOLDER_TEMP 50

#define SOL_HEAT_OFF 0
#define SOL_HEAT_ON 1
#define SOL_HEAT_SLEEP 2
#define SOL_HEAT_ON_FIX_POWER 3

#define PORT_VIBRO PIND
#define VIBRO (1 << PIND3)

class Solder{
  private:
  public:
    static uint16_t EEMEM arefTemp1; 
    static uint16_t EEMEM arefTemp2;
    static uint16_t EEMEM arefAdc1;
    static uint16_t EEMEM arefAdc2;
    static uint16_t EEMEM atempSets;
    Solder();
    uint16_t temp;
    uint16_t currentTemp;
    uint8_t isPowered;
    float k;
    float b;
    uint16_t refTemp1; 
    uint16_t refTemp2;
    uint16_t refAdc1;
    uint16_t refAdc2;
    uint16_t adc;
    uint8_t power;
    void setPowerOn();
    void setPowerOff();
    void setPowerFixOnOff();
    void setTemp(uint16_t temp);
    void setTemp(bool isClockwise);
    void setPowerSleep();
    void setPower(uint8_t power);
    void setPower(bool isClockwise);
    void tempConversion(uint16_t adc);
    void atributesConversion();
    void setEtalon(bool isClockwise);
    void fixEtalon();
    void readEeprom();
    void updateEeprom();
};

#endif /* SOLDER_H_ */