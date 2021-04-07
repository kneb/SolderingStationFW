/*
 * lcd.cpp
 *
 * Created: 07.04.2021 15:33:48
 *  Author: Neb Konstantin Viktorovich
 */ 

#include "Headers/globals.h"
#include "Headers/lcd.h"

void Lcd::printMain(){
  char buf[17];
  hd44780.goTo(0, 0);
  sprintf(buf, "\x04%03d\x02\x7f\x03%2d%%  %03d\x02",
  thermoFan.currentTemp, thermoFan.fan, thermoFan.setTemp);
  hd44780.sendString(buf);
  hd44780.goTo(0, 1);
  sprintf(buf, "%03d\x02 \x01\x05 \x06  %03d\x02", solder.currentTemp, solder.setTemp);
  hd44780.sendChar(0);
  hd44780.sendString(buf);
}

void Lcd::printLogo(){
  hd44780.goTo(1, 0);
  hd44780.sendString("Soldering");
  hd44780.goTo(3, 1);
  hd44780.sendString("Station 1.0");
}