/*
 * lcd.cpp
 *
 * Created: 07.04.2021 15:33:48
 *  Author: Neb Konstantin Viktorovich
 */ 

#include "Headers/globals.h"
#include "Headers/lcd.h"

const uint8_t curType[4] PROGMEM = {CURSOR_LEFT_ARROW, CURSOR_RIGHT_ARROW,
                            CURSOR_LEFT_ANGLE, CURSOR_RIGHT_ANGLE};

const uint16_t curPosDashboard[6] PROGMEM = {
  0x5100, 0x5000, 0xA000, 0xB001, 0xB101, 0xA100
};
const uint16_t curPosRootMenu[5] PROGMEM = {
  0x6100, 0x6000, 0xD000, 0xE001, 0xD100
};
const uint16_t curPosCalibration[5] PROGMEM = {
  0x4100, 0x4000, 0xE001, 0xE101, 0x9101
};

Lcd::Lcd(){
  this->menu.isEdit = 0;
  this->menu.param = 1;
  this->menu.level = 0;
}

void Lcd::printMain(){
  cli();
  hd44780.clear();
  hd44780.goTo(0, 0);
  hd44780.sendStringFlash(PSTR("\x04"));
  this->printInt(1, 0, thermoFan.currentTemp, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(6, 0);
  hd44780.sendStringFlash(PSTR("\x03"));
  this->printInt(7, 0, thermoFan.fan, 3, false);
  hd44780.sendStringFlash(PSTR("%"));
  this->printInt(12, 0, thermoFan.temp, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(0, 1);
  hd44780.sendChar(0);
  this->printInt(1, 1, solder.currentTemp, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(9, 1);
  hd44780.sendStringFlash(PSTR("\x06"));
  this->printInt(12, 1, solder.temp, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  this->printMenuCursor(CURSOR_TYPE_ARROW);
  sei();
} 

void Lcd::printMenu(){
  cli();
  hd44780.clear();
  hd44780.goTo(0, 0);
  hd44780.sendStringFlash(PSTR("cal.TF   Save  x"));
  hd44780.goTo(0, 1);
  hd44780.sendStringFlash(PSTR("cal.Sl  Delay"));
  this->printMenuCursor(CURSOR_TYPE_ARROW);
  sei();
}

void Lcd::printCalibration(uint8_t calibrationMenu = CALIBRATION_THERMOFAN){
  uint8_t temp1;
  uint8_t temp2;
  uint16_t adc1;
  uint16_t adc2;
  if (calibrationMenu == CALIBRATION_THERMOFAN){
    temp1 = thermoFan.refTemp1;
    temp2 = thermoFan.refTemp2;
    adc1 = thermoFan.refAdc1;
    adc2 = thermoFan.refAdc2;
  } else {
     
  }
  uint8_t temp;
  cli();
  hd44780.clear();
  this->printInt(0, 0, temp1, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  this->printInt(5, 0, adc1, 4);
  hd44780.sendChar(calibrationMenu);
  this->printInt(10, 0, thermoFan.currentTemp, 3);
  hd44780.sendStringFlash(PSTR("\x02 x"));
  this->printInt(0, 1, temp2, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  this->printInt(5, 1, adc2, 4);
  this->printInt(10, 1, thermoFan.fan, 3);
  hd44780.sendStringFlash(PSTR("% s"));
  this->printMenuCursor(CURSOR_TYPE_ARROW);
  sei();
}

void Lcd::printInt(uint8_t x, uint8_t y, uint16_t source, uint8_t len, bool zero){
  char buf[5];
  hd44780.goTo(x, y);
  itoa(buf, source, len, zero);
  hd44780.sendString(buf);  
}

void Lcd::printLogo(){
  hd44780.goTo(1, 0);
  hd44780.sendStringFlash(PSTR("Soldering"));
  hd44780.goTo(3, 1);
  hd44780.sendStringFlash(PSTR("Station 1.0"));
}

void Lcd::printIconsStatus(){
  hd44780.goTo(6, 1);
  if ((PORT_VIBRO & VIBRO) == 0){
    hd44780.sendStringFlash(PSTR("\x07"));
  } else {
    hd44780.sendStringFlash(PSTR("\x01"));
  }
  if ((PORT_GERKON & GERKON) == 0){ //ThermoFan on stand
    hd44780.sendStringFlash(PSTR("\x05"));
  } else {
    hd44780.sendStringFlash(PSTR("\xc6"));
  }  
}

void Lcd::printMenuCursor(uint8_t cursorType = CURSOR_TYPE_ARROW){
  uint16_t buf = 0;
  switch (this->menu.level){ 
    case 0: //Dashboard cursor moving 
      buf = pgm_read_word(&curPosDashboard[this->menu.param]);    
      break;
    case 1: //Root menu cursor moving
      buf = pgm_read_word(&curPosRootMenu[this->menu.param]);    
      break;
    case 2:
    case 3:
      buf = pgm_read_word(&curPosCalibration[this->menu.param]);
      break;
  } 
  uint8_t x = buf >> 12;
  uint8_t y = (buf >> 8) & 0x0f;
  uint8_t cursorId = pgm_read_byte(&curType[(this->menu.isEdit<<1)|(buf&1)]);
  if (cursorType != CURSOR_TYPE_ARROW){
    cursorId = cursorType;
  }
  hd44780.goTo(x, y);
  hd44780.sendChar(cursorId);
}

void itoa(char* buf, uint16_t source, uint8_t len, bool zero){
  uint16_t div = 1;
  uint8_t i = 1;
  while (i < len){
    div *= 10;
    i++;
  }
  while (div > 0)
  {
    *buf = source / div;
    if (*buf > 0){
      *buf += 0x30;
      buf++;
      zero = true;
    } else if (zero) {
      *buf = 0x30;
      buf++;
    }
    source %= div;
    div /= 10;
  }
  *buf = '\0';  
}

void Lcd::swapIsEdit(){
  this->menu.isEdit ^= 1;
  this->printMenuCursor(CURSOR_TYPE_ARROW);
}
