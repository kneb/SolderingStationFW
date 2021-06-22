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
  OCR2 = this->fan*2 + this->fan/2;
}

void ThermoFan::setPowerOn(){
  this->isPowered = TF_HEAT_ON;
  LED_PORT &= ~LED_FEN;
  TCCR2 |= (1 << COM21);

  OCR1AL = 125;
  TCCR1A |= (1 << COM1A1);
}

void ThermoFan::setPowerOff(){
  this->isPowered = TF_HEAT_OFF;
  LED_PORT |= LED_FEN;
  TCCR2 &= ~(1 << COM21);
  TCCR1A &= ~(1 << COM1A1);
}

void ThermoFan::setPowerSleep(){
  this->isPowered = TF_ON_HOLDER;
  this->fanBuf = this->fan;
  this->setFan((uint8_t)99);
  TCCR1A &= ~(1 << COM1A1);
}

void ThermoFan::setFan(uint8_t fan){
  this->fan = fan;
  lcd.printInt(7, 0, thermoFan.fan, 2);
  OCR2 = fan*2 + fan/2;
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

void ThermoFan::getStatus(){
  if ((PORT_GERKON & GERKON) == 0){ //ThermoFan on stand
    if (this->isPowered == 1){
      this->setPowerSleep();
    } else {
      if (this->isPowered == 2) {
        LED_PORT ^= LED_FEN; // Blink Led fan
      }
    }
  } else {
    if (this->isPowered == 2){
      this->setFan(this->fanBuf);
      this->setPowerOn();
    }
  }
}

