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
    _delay_ms(10); //time for contact unbounce
    if (((PIN_ENCEDER_SW & ENCEDER_SW) == 0) && (this->buttonDown == 0)){
      this->onClickButton();
      this->buttonDown = 1;
    }
  } else {
    this->buttonDown = 0;
  }
}

void Encoder::onClickButton(){
  if (lcd.menu.level == 0){ //Root menu
    switch (lcd.menu.param){
      case 0: //Soldering power 
        if (solder.isPowered == 0){
          solder.setPowerOn();
        } else {
          solder.setPowerOff();
        }
      break;
      case 1: //Thermofan power
        if (thermoFan.isPowered == 0){
          thermoFan.setPowerOn();
        } else {
          thermoFan.setPowerOff();
        }
      break;
      case 2:
        
      break;   
      default:
        
      break;
    } 
  } else {

  }  
}

void Encoder::onRotation(bool isClockwise){
  if (lcd.menu.isEdit == 0) {
    lcd.changeParam(isClockwise);
  } else {

  }

  /*
  char buf[4];
  switch (lcd.param){
    case 1:
      if (isClockwise) thermoFan.fan++; else thermoFan.fan--;
      lcd.goTo(7, 0);
      sprintf(buf, "%d", thermoFan.fan);
      lcd.sendString(buf);
      lcd.goTo(8, 0);
      break;
    case 2:
      if (isClockwise) thermoFan.setTemp++; else thermoFan.setTemp--;
      lcd.goTo(12, 0);
      sprintf(buf, "%03d", thermoFan.setTemp);
      lcd.sendString(buf);
      lcd.goTo(14, 0);
      break;
    case 3:
      if (isClockwise) solder.setTemp++; else solder.setTemp--;
      lcd.goTo(12, 1);
      sprintf(buf, "%03d", solder.setTemp);
      lcd.sendString(buf);
      lcd.goTo(14, 1);
      break;
  }
  */
}
