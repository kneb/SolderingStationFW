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
  switch(lcd.menu.level){ 
    case 0: //Dashboard
    switch(lcd.menu.param){
      case 0: //Soldering power on\off
        sound.beep(300, 1, 0);
        (solder.isPowered == 0) ? solder.setPowerOn() : solder.setPowerOff();   
        break;
      case 1: //Thermofan power on\off
        sound.beep(300, 1, 0);
        (thermoFan.isPowered == 0) ? thermoFan.setPowerOn() : thermoFan.setPowerOff();     
        break;
      case 5: //Go to Root menu 
        lcd.menu.level = 1;
        lcd.menu.param = 3;
        lcd.printMenu();
        break;
      default:
        sound.beep(200, 1, 0);
        lcd.swapIsEdit();
    }
    break;
    case 1: //Root menu
      switch(lcd.menu.param){
        case 0: //Calibration Solder
          lcd.menu.level = 2;
          lcd.menu.param = 2;
          lcd.printCalibration(CALIBRATION_SOLDER);
          break;
        case 1: //Calibration ThermoFan
          lcd.menu.level = 3;
          lcd.menu.param = 2;
          lcd.printCalibration(CALIBRATION_THERMOFAN);
          break;
        case 2: //Save current set's
          break;
        case 3: //Exit the root menu
          lcd.menu.level = 0;
          lcd.menu.param = 5;
          lcd.printMain();
          break;
        case 4: //Delay
          break;
      }
      break;
    case 2: //Calibration menu Solder
      switch(lcd.menu.param){
        case 0: //Set etalon2
        case 1: //Set etalon1
          sound.beep(200, 1, 0);
          lcd.swapIsEdit();
          if (lcd.menu.isEdit == 0) {
            thermoFan.fixEtalon();
          }
          break;
        case 2: //Exit the calibration menu
          solder.readEeprom();
          lcd.menu.level = 1;
          lcd.menu.param = 0;
          lcd.printMenu();
          break;
        case 3: //Save etalons to eeprom
          solder.updateEeprom();
          break;
        case 4: //Set power on\off
          break;
        case 5: //Set power editing
          sound.beep(200, 1, 0);
          lcd.swapIsEdit();
          break;
      }      
      break;
    case 3: //Calibration menu ThermoFan
      switch(lcd.menu.param){
        case 0: //Set etalon2
        case 1: //Set etalon1
          sound.beep(200, 1, 0);
          lcd.swapIsEdit();
          if (lcd.menu.isEdit == 0) {
            thermoFan.fixEtalon();
          }
          break;
        case 2: //Exit the calibration menu
          thermoFan.readEeprom();
          lcd.menu.level = 1;
          lcd.menu.param = 1;
          lcd.printMenu();
          break;
        case 3: //Save etalons to eeprom
          thermoFan.updateEeprom();
          break;
        case 4: //Set power on\off
          break;
        case 5: //Set power editing
          sound.beep(200, 1, 0);
          lcd.swapIsEdit();
          break;
      }      
      break;
  }
}

void Encoder::onRotation(bool isClockwise){
  if (lcd.menu.isEdit == 0){ //Moving cursors
    if (lcd.menu.level == 0){ //Dashboard
      lcd.printMenuCursor(CURSOR_TYPE_EMPTY);
      if (isClockwise == true){       
        lcd.menu.param = (lcd.menu.param == 5) ? 0 : (lcd.menu.param + 1);
      } else {
        lcd.menu.param = (lcd.menu.param == 0) ? 5 : (lcd.menu.param - 1);    
      }
      lcd.printMenuCursor(CURSOR_TYPE_ARROW);
    } else if (lcd.menu.level == 1){ //Root menu
      lcd.printMenuCursor(CURSOR_TYPE_EMPTY);
      if (isClockwise == true){       
        lcd.menu.param = (lcd.menu.param == 4) ? 0 : (lcd.menu.param + 1);
      } else {
        lcd.menu.param = (lcd.menu.param == 0) ? 4 : (lcd.menu.param - 1);    
      }
      lcd.printMenuCursor(CURSOR_TYPE_ARROW);
    } else if ((lcd.menu.level == 2)||(lcd.menu.level == 3)) { //Calibration menu Thermofan
      lcd.printMenuCursor(CURSOR_TYPE_EMPTY);
      if (isClockwise == true){       
        lcd.menu.param = (lcd.menu.param == 5) ? 0 : (lcd.menu.param + 1);
      } else {
        lcd.menu.param = (lcd.menu.param == 0) ? 5 : (lcd.menu.param - 1);    
      }
      lcd.printMenuCursor(CURSOR_TYPE_ARROW);
    }

  } else { //Edit param
    if (lcd.menu.level == 0){ //Dashboard
      switch (lcd.menu.param){
        case 2: //Changed fan
          thermoFan.setFan(isClockwise);
          break;
        case 3: //Changed Temp fan
          thermoFan.setTemp(isClockwise);
          break;
        case 4: //Changed Temp solder
          solder.setTemp(isClockwise);
          break;  
      }
    } else if (lcd.menu.level == 3){ //Calibration menu Thermofan
      switch (lcd.menu.param){
        case 0: //Changed etalon2
          thermoFan.setEtalon(isClockwise);
          break;
        case 1: //Changed etalon1
          thermoFan.setEtalon(isClockwise);
          break;
        case 5: //Changed power
          thermoFan.setPower(isClockwise);
          break;
      }
    } else if (lcd.menu.level == 2){ //Calibration menu Solder
      switch (lcd.menu.param){
        case 0: //Changed etalon2
          solder.setEtalon(isClockwise);
          break;
        case 1: //Changed etalon1
          solder.setEtalon(isClockwise);
          break;
        case 5: //Changed power
          solder.setPower(isClockwise);
          break;
      }
    }
  }
 
}
