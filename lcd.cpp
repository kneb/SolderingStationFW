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

/*
void Lcd::changeParam(bool isClockwise){

}
*/

void Lcd::printIconsStatus(){
  
}

void Lcd::printMenuCursor(uint8_t cursorType = CURSOR_TYPE_ARROW){
  uint8_t x = 0;
  uint8_t y = 0;
  uint8_t cursorId = 0;
  if (this->menu.level == 0){
    switch (this->menu.param){
      case 1:
        x = 5; y = 0;
        cursorId = CURSOR_LEFT_ARROW;
        break;
      case 2:
        x = 10; y = 0;
        cursorId = CURSOR_LEFT_ARROW;
        break;
      case 3:
        x = 11; y = 0;
        cursorId = CURSOR_RIGHT_ARROW;
        break;
      case 4:
        x = 11; y = 1;
        cursorId = CURSOR_RIGHT_ARROW;
        break;
      case 5:
        x = 10; y = 1;
        cursorId = CURSOR_LEFT_ARROW;
        break;
      case 6:
        x = 5; y = 1;
        cursorId = CURSOR_LEFT_ARROW;
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