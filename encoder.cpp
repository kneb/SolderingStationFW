/*
 * encoder.cpp
 *
 * Created: 08.02.2021 17:57:25
 *  Author: Neb Konstantin Viktorovich
 */
#include "Headers/globals.h"
#include "Headers/hd44780.h"
#include "Headers/encoder.h"

Encoder::Encoder(){
  this->buttonDown = 0;
}

void Encoder::getButtonStatus(){
  if ((PIN_ENCEDER_SW & ENCEDER_SW) == 0){
    _delay_ms(10);
    if (((PIN_ENCEDER_SW & ENCEDER_SW) == 0) && (this->buttonDown == 0)){
      this->onClickButton();
      this->buttonDown = 1;
    }
  } else {
    this->buttonDown = 0;
  }
}

void Encoder::onClickButton(){
  lcd.changeParam();
}

void Encoder::onRotation(bool isClockwise){
  char buf[4];
  switch (lcd.param){
    case 1:
      if (isClockwise) thermoFan.fan++; else thermoFan.fan--;
      lcd.goTo(7, 0);
      sprintf(buf, "%2d", thermoFan.fan);
      lcd.sendString(buf);
      break;
    case 2:
      if (isClockwise) thermoFan.setTemp++; else thermoFan.setTemp--;
      lcd.goTo(12, 0);
      sprintf(buf, "%03d", thermoFan.setTemp);
      lcd.sendString(buf);
      break;
    case 3:
      if (isClockwise) solder.setTemp++; else solder.setTemp--;
      lcd.goTo(12, 1);
      sprintf(buf, "%03d", solder.setTemp);
      lcd.sendString(buf);
      break;
  }
}
