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
    if (lcd.menu.param == 0){ //Soldering power 
      sound.beep(300, 1, 0);
      (solder.isPowered == 0) ? solder.setPowerOn() : solder.setPowerOff();   
    } else if (lcd.menu.param == 1){ //Thermofan power
      sound.beep(300, 1, 0);
      (thermoFan.isPowered == 0) ? thermoFan.setPowerOn() : thermoFan.setPowerOff();     
    } else if (lcd.menu.param == 5){
      
    } else {
      sound.beep(300, 1, 0);
      lcd.swapIsEdit();
    }    
  } else {

  }  
}

void Encoder::onRotation(bool isClockwise){
  if (lcd.menu.isEdit == 0){ //Moving cursors
    if (lcd.menu.level == 0){ //Root menu
      lcd.printMenuCursor(CURSOR_TYPE_EMPTY);
      if (isClockwise == true){       
        lcd.menu.param = (lcd.menu.param == 5) ? 0 : (lcd.menu.param + 1);
      } else {
        lcd.menu.param = (lcd.menu.param == 0) ? 5 : (lcd.menu.param - 1);    
      }
      lcd.printMenuCursor(CURSOR_TYPE_ARROW);
    }
  } else { //Edit param
    if (lcd.menu.level == 0){ //Root menu
      switch (lcd.menu.param){
        case 2:
          thermoFan.setFan(isClockwise);
          break;
        case 3:
          thermoFan.setTemp(isClockwise);
          break;
        case 4:
          solder.setTemp(isClockwise);
          break;  
      }
    }    
  }
 
}
