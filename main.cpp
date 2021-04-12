/*
 * main.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */ 
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "Headers/globals.h"
#include "Headers/hd44780.h"
#include "Headers/encoder.h"


int main(void){
  init();
  lcd.printLogo();
  _delay_ms(1000);
  _delay_ms(1000);
  lcd.printMain();

  sei();
  while (true){
	  _delay_ms(20);
    encoder.getButtonStatus();
    
  }
}

