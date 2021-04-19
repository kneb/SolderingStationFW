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
  this->menu.level = 0;
  this->menu.param = 1;
}

void Lcd::printMain(){
  hd44780.clear();
  char buf[4];
  hd44780.goTo(0, 0);
  hd44780.sendStringFlash(PSTR("\x04"));
  itoa(buf, thermoFan.currentTemp, 3);
  hd44780.sendString(buf);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(6, 0);
  hd44780.sendStringFlash(PSTR("\x03"));
  itoa(buf, thermoFan.fan, 2);
  hd44780.sendString(buf);
  hd44780.sendStringFlash(PSTR("%"));
  hd44780.goTo(12, 0);
  itoa(buf, thermoFan.setTemp, 3);
  hd44780.sendString(buf);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(0, 1);
  hd44780.sendChar(0);
  itoa(buf, solder.currentTemp, 3);
  hd44780.sendString(buf);
  hd44780.sendStringFlash(PSTR("\x02"));
  hd44780.goTo(9, 1);
  hd44780.sendStringFlash(PSTR("\x06"));
  hd44780.goTo(12, 1);
  itoa(buf, solder.setTemp, 3);
  hd44780.sendString(buf);
  hd44780.sendStringFlash(PSTR("\x02"));
}

void Lcd::printLogo(){
  hd44780.goTo(1, 0);
  hd44780.sendStringFlash(PSTR("Soldering"));
  hd44780.goTo(3, 1);
  hd44780.sendStringFlash(PSTR("Station 1.0"));
  
}

void Lcd::changeParam(bool isClockwise){

}

void Lcd::printIconsStatus(){
  
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