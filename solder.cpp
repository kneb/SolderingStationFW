/*
 * solder.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */ 

#include "Headers/globals.h"
#include "Headers/solder.h"

Solder::Solder(){
  this->currentTemp = 0;
  this->temp = 250;
  this->isPowered = 0;
}

void Solder::setPowerOn(){
  this->isPowered = SOL_HEAT_ON;
  LED_PORT &= ~LED_SOL;
}

void Solder::setPowerOff(){
  this->isPowered = SOL_HEAT_OFF;
  LED_PORT |= LED_SOL;
}

void Solder::setTemp(uint16_t temp){
  this->temp = temp;
  lcd.printInt(12, 1, solder.temp, 3);
}

void Solder::setTemp(bool isClockwise){
  if (isClockwise){
    if (this->temp < MAX_SOLDER_TEMP){
      this->setTemp(this->temp+5);
    }
  } else {
    if (this->temp > MIN_SOLDER_TEMP){
      this->setTemp(this->temp-5);
    }
  }
}