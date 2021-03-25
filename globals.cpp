/*
 * globals.cpp
 *
 * Created: 09.02.2021 13:59:12
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/globals.h"

HD44780 lcd;
Encoder encoder;
ThermoFan thermoFan;
Solder solder;

void init_ports(){
  DDRB = 0b00000000;
  DDRC = 0b00000000;  
  DDRD = 0b11110011; 

  PORTC = 0b00010000;
 
  MCUCR |= (1 << ISC00)|(1 << ISC10);    
  GICR |= (1 << INT0);
}

ISR(INT0_vect){
  GICR &= ~(1 << INT0);
  uint8_t b = (PINC & 32) >> 5;
  _delay_ms(1);
  uint8_t a = (PIND & 4) >> 2;
  if (a == b){
    encoder.onRotation(false);
  } else {
    encoder.onRotation(true);
  }
  GIFR |= (1 << INTF0);
  GICR |= (1 << INT0);
}