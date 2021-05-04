/*
 * thermofan.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/globals.h"
#include "Headers/thermofan.h"

ThermoFan::ThermoFan(){
  this->fan = 50;
  this->temp = 150;
  this->currentTemp = 0;
}

void ThermoFan::setPowerOn(){
  this->isPowered = TF_HEAT_ON;
  LED_PORT &= ~LED_FEN;
}

void ThermoFan::setPowerOff(){
  this->isPowered = TF_HEAT_OFF;
  LED_PORT |= LED_FEN;
}

void ThermoFan::setFan(uint8_t fan){
  this->fan = fan;
  lcd.printInt(7, 0, thermoFan.fan, 2);
}

void ThermoFan::setFan(bool isClockwise){
  if (isClockwise){
    if (this->fan < 99){
      this->setFan(++this->fan);
    }      
  } else {
    if (this->fan > 30){
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

