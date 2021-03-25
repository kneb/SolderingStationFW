/*
 * main.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */ 
#ifndef __AVR_ATmega8A__
#define __AVR_ATmega8A__
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "Headers/globals.h"
#include "Headers/hd44780.h"
#include "Headers/encoder.h"


int main(void){
  init_ports();
  lcd.init();
  lcd.printMain();

  sei();
  while (true){
	  _delay_ms(20);
    encoder.getButtonStatus();
    
  }
}

