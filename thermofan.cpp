/*
 * thermofan.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/globals.h"
#include "Headers/thermofan.h"
#include <avr/eeprom.h>

const uint16_t EEMEM ThermoFan::arefTemp1 = 10;
const uint16_t EEMEM ThermoFan::arefTemp2 = 200;
const uint16_t EEMEM ThermoFan::arefAdc1 = 10;
const uint16_t EEMEM ThermoFan::arefAdc2 = 500;
const uint16_t EEMEM ThermoFan::atempSets = 250;
const uint8_t EEMEM ThermoFan::afanSets = 99;

ThermoFan::ThermoFan(){
  this->fan = 50;
  this->temp = 150;
  this->currentTemp = 0;
  OCR2 = this->fan*2 + this->fan/2;
}

void ThermoFan::readEeprom(){
  this->temp = eeprom_read_word(&ThermoFan::atempSets);
  this->fan = eeprom_read_byte(&ThermoFan::afanSets);
  this->refTemp1 = eeprom_read_word(&ThermoFan::arefTemp1);
  this->refTemp2 = eeprom_read_word(&ThermoFan::arefTemp2);
  this->refAdc1 = eeprom_read_word(&ThermoFan::arefAdc1);
  this->refAdc2 = eeprom_read_word(&ThermoFan::arefAdc2);
  this->atributesConversion();
}

void ThermoFan::setPowerOn(){
  this->isPowered = TF_HEAT_ON;
  LED_PORT &= ~LED_FEN; //Led on
  TCCR2 |= (1 << COM21); //PWM Fan on

  OCR1AL = 125;
  TCCR1A |= (1 << COM1A1); //PWM Temp on
}

void ThermoFan::setPowerOff(){
  this->isPowered = TF_HEAT_OFF;
  LED_PORT |= LED_FEN; //Led off
  TCCR2 &= ~(1 << COM21); //PWM Fan off
  TCCR1A &= ~(1 << COM1A1); //PWM Temp off
}

void ThermoFan::setPowerSleep(){
  this->isPowered = TF_ON_HOLDER;
  this->fanBuf = this->fan;
  this->setFan((uint8_t)100);
  TCCR1A &= ~(1 << COM1A1); //PWM Temp off
}

void ThermoFan::setFan(uint8_t fan){
  this->fan = fan;
  lcd.printInt(7, 0, fan, 3, false);
  if ((fan > 97) && (fan < 100)){
    hd44780.sendStringFlash(PSTR("%"));
  }
  if (fan==100){
    OCR2 = 255;
  } else
  OCR2 = fan*2 + fan/2;
}

void ThermoFan::setFan(bool isClockwise){
  if (isClockwise){
    if (this->fan < 100){
      this->setFan(++this->fan);
    }      
  } else {
    if (this->fan > 20){
      this->setFan(--this->fan);
    }
  }
}

void ThermoFan::setTemp(uint16_t temp){
  this->temp = temp;
  lcd.printInt(12, 0, thermoFan.temp, 3);
}

void ThermoFan::setTemp(bool isClockwise){
  if (isClockwise){
    if (this->temp < MAX_TFAN_TEMP){
      this->setTemp(this->temp+5);
    }
  } else {
    if (this->temp > MIN_TFAN_TEMP){
      this->setTemp(this->temp-5);
    }
  }
}

void ThermoFan::getStatus(){
  if ((PORT_GERKON & GERKON) == 0){ //ThermoFan on stand
    if (this->isPowered == TF_HEAT_ON){
      this->setPowerSleep();
    } else if (this->isPowered == TF_ON_HOLDER) {
        LED_PORT ^= LED_FEN; // Blink Led fan
    }
  } else {
    if (this->isPowered == TF_ON_HOLDER){
      this->setFan(this->fanBuf);
      this->setPowerOn();
    }
  }
}

void ThermoFan::tempConversion(uint16_t adc){
  this->currentTemp = this->k*adc + this->b;
}

void ThermoFan::atributesConversion(){
  if ((this->refAdc2-this->refAdc1) != 0){
    this->k = (float)(this->refTemp2-this->refTemp1) / 
              (this->refAdc2-this->refAdc1);
  } else {
    this->k = 1.;
  }
  this->b = this->refTemp2 - this->k*this->refAdc2;
}

void ThermoFan::setEtalon(uint8_t n, bool isClockwise){
  if (n == 1) {
    if (isClockwise){
      this->refTemp1 += 1;
    } else {
      this->refTemp1 -= 1;
    }
    lcd.printInt(0, 0, this->refTemp1, 3);
  } else {
    if (isClockwise){
      this->refTemp2 += 1;
    } else {
      this->refTemp2 -= 1;
    }
    lcd.printInt(0, 0, this->refTemp2, 3);
  }
}

