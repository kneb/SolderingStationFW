/*
 * lcd.cpp
 *
 * Created: 07.04.2021 15:33:48
 *  Author: Neb Konstantin Viktorovich
 */ 

#include "Headers/globals.h"
#include "Headers/lcd.h"

Lcd::Lcd(){
  this->menu.isEdit = 0;
  this->menu.param = 1;
  this->menu.level = 0;
}

void Lcd::printMain(){
  hd44780.clear();
  hd44780.goTo(0, 0);
  hd44780.sendStringFlash(PSTR("\x04"));
  this->printInt(1, 0, thermoFan.currentTemp, 3);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(6, 0);
  hd44780.sendStringFlash(PSTR("\x03"));
  this->printInt(7, 0, thermoFan.fan, 2);
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
}

void Lcd::printInt(uint8_t x, uint8_t y, uint16_t source, uint8_t len){
  char buf[4];
  hd44780.goTo(x, y);
  itoa(buf, source, len);
  hd44780.sendString(buf);  
}

void Lcd::printLogo(){
  hd44780.goTo(1, 0);
  hd44780.sendStringFlash(PSTR("Soldering"));
  hd44780.goTo(3, 1);
  hd44780.sendStringFlash(PSTR("Station 1.0"));
}

void Lcd::printIconsStatus(){
  
}

void Lcd::printMenuCursor(uint8_t cursorType = CURSOR_TYPE_ARROW){
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t cursorId = 0;
  uint8_t left, right;
  if (this->menu.isEdit == 0){
    left = CURSOR_LEFT_ARROW;
    right = CURSOR_RIGHT_ARROW;
  } else {
    left = CURSOR_LEFT_ANGLE;
    right = CURSOR_RIGHT_ANGLE;
  }
  if (this->menu.level == 0){
    switch (this->menu.param){
      case 0:
        x = 5; y = 1;
        cursorId = left;
        break;    
      case 1:
        x = 5; y = 0;
        cursorId = left;
        break;
      case 2:
        x = 10; y = 0;
        cursorId = left;
        break;
      case 3:
        x = 11; y = 0;
        cursorId = right;
        break;
      case 4:
        x = 11; y = 1;
        cursorId = right;
        break;
      case 5:
        x = 10; y = 1;
        cursorId = left;
        break;
    }
  }    
  hd44780.goTo(x, y);
  if (cursorType == CURSOR_TYPE_EMPTY){
    hd44780.sendChar(0x20);
  } else if (cursorType == CURSOR_TYPE_ARROW){
    hd44780.sendChar(cursorId);
  } else {
    hd44780.sendChar(cursorType);
  }  
}

void itoa(char* buf, uint16_t source, uint8_t lenZero){
  uint16_t div = 100;
  uint8_t i = 3;
  while (i > 0)
  {
    *buf = source / div;
    if (*buf > 0){
      *buf += 0x30;
      buf++;
    } else if (lenZero >= i) {
      *buf = 0x30;
      buf++;
    } else *buf = 0x20;
    source %= div;
    div /= 10;
    i--;
  }
  *buf = '\0';  
}

void Lcd::swapIsEdit(){
  this->menu.isEdit ^= 1;
  this->printMenuCursor(CURSOR_TYPE_ARROW);
}
