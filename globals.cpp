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

uint8_t tim = 0;

void init_ports(){
  PORTB = 0b00110000;
  DDRB = 0b00110000;
  DDRC = 0b00000100;
  DDRD = 0b11110011;

  PORTC = 0b00010000;

  
  MCUCR |= (1 << ISC00)|(1 << ISC10); //any logical change on INT0 and INT1
  GICR |= (1 << INT0);

  TCCR0 = (1 << CS00)|(1 << CS02); //tim0 divider 1024
  TIMSK = (1 << TOIE0);
  
}

ISR(INT0_vect){ //the encoder has been turned
  GICR &= ~(1 << INT0); //disable ext.int. on INT0
  uint8_t b = (PINC & 32) >> 5;
  _delay_ms(1);
  uint8_t a = (PIND & 4) >> 2;
  if (a == b){
    encoder.onRotation(false);
  } else {
    encoder.onRotation(true);
  }
  GIFR |= (1 << INTF0);
  GICR |= (1 << INT0); //enable ext.int. on INT0
}

ISR(TIMER0_OVF_vect){
  if (tim < 61) {
    tim ++;
  } else { //The code is executable with a frequency of one second
    tim = 0;
    
  }

}
