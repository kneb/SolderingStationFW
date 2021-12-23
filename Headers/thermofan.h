/*
 * thermofan.h
 *
 * Created: 07.02.2021 2:34:45
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef THERMOFAN_H_
#define THERMOFAN_H_

#include <avr/io.h>
#include <avr/eeprom.h>

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
    static const uint16_t EEMEM arefTemp1; 
    static const uint16_t EEMEM arefTemp2;
    static const uint16_t EEMEM arefAdc1;
    static const uint16_t EEMEM arefAdc2;
    static const uint16_t EEMEM atempSets;
    static const uint8_t EEMEM afanSets;

    uint8_t fan;
    uint8_t fanBuf;
    uint16_t temp;
    uint16_t currentTemp;
    uint8_t isPowered;
    float k;
    float b;
    uint16_t refTemp1; 
    uint16_t refTemp2;
    uint16_t refAdc1;
    uint16_t refAdc2;

    ThermoFan();
    void setPowerOn();
    void setPowerOff();
    void setPowerSleep();
    void setFan(uint8_t fan);
    void setFan(bool isClockwise);
    void setTemp(uint16_t temp);
    void setTemp(bool isClockwise);
    void getStatus();
    void readEeprom();
    void tempConversion(uint16_t adc);
    void atributesConversion();
    void setEtalon(uint8_t n, bool isClockwise);
};


#endif /* THERMOFAN_H_ */