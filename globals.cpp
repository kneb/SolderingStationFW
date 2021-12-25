/*
 * globals.cpp
 *
 * Created: 09.02.2021 13:59:12
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/globals.h"
#include <avr/pgmspace.h>

HD44780 hd44780;
Lcd lcd;
Encoder encoder;
ThermoFan thermoFan;
Solder solder;
Sound sound;

uint8_t tim = 0;

void init(){
  PORTB = 0b00110001;
  DDRB = 0b00111111;
  DDRC = 0b00000100;
  DDRD = 0b11110011;

  PORTC = 0b00010000;
  
  hd44780.init();
  
  MCUCR |= (1 << ISC00)|(1 << ISC10); //any logical change on INT0 and INT1
  GICR |= (1 << INT0);

  TCCR0 = (1 << CS00)|(1 << CS02); //tim0 divider 1024
  TIMSK = (1 << TOIE0);

  TCCR1A = (1 << WGM11);
  TCCR1B = (1 << WGM13)|(1 << WGM12)|(1 << CS12)|(1 << CS10);
  ICR1 = 15625;

  TCCR2 = (1 << WGM21)|(1 << WGM20)|(1 << CS22)|(0 << CS21)|(0 << CS20);

  ADMUX = (1 << REFS1)|(1 << REFS0); //internal 2.56v
  ADCSRA = (1 << ADEN)|(1 << ADIE)|(1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0); //128kHz
  
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

ISR(TIMER0_OVF_vect){ //Timer0 at frequency ~61Hz (~16,4ms)
  sound.getBeep();
  if (tim < 61){   
    tim ++;
    if ((tim % 30) == 0){
      thermoFan.getStatus();
      if (lcd.menu.level == 0){
        lcd.printIconsStatus();
      }
    }
    if ((tim % 15) == 0){
      ADCSRA |= (1 << ADSC); //start ADC converter
      
    }
  } else { //The code is executable with a frequency of one second
    tim = 0;
    if (lcd.menu.level == 0){ //Dashboard
      lcd.printInt(1, 0, thermoFan.currentTemp, 3);
      lcd.printInt(1, 1, solder.currentTemp, 3);
    } else if (lcd.menu.level == 3){ //Calibration menu thermofan
      lcd.printInt(10, 0, thermoFan.currentTemp, 3);
      if(lcd.menu.isEdit == 1){
        if (lcd.menu.param == 0){
          lcd.printInt(5, 1, thermoFan.adc, 4);
        } else if (lcd.menu.param == 1) {
          lcd.printInt(5, 0, thermoFan.adc, 4);
        }                  
      }
    } else if (lcd.menu.level == 2){ //Calibration menu solder
      lcd.printInt(10, 0, solder.currentTemp, 3);
      if(lcd.menu.isEdit == 1){
        if (lcd.menu.param == 0){
          lcd.printInt(5, 1, solder.adc, 4);
        } else if (lcd.menu.param == 1) {
          lcd.printInt(5, 0, solder.adc, 4);
        }                  
      }
    }     
    
  }
}

void Sound::getBeep(){
  if (this->beepCount > 0){
    if (this->beepTim > 0){
      this->beepTim--;
    } else {
      SOUND_PORT ^= SOUND_PIN;
      this->beepCount--;
      this->beepTim = (this->beepCount%2 == 0) ? this->beepDurationDelay : this->beepDuration;
    }
  }  
}

void Sound::beep(uint16_t duration_ms=500, uint8_t count=1, uint16_t delay_ms=500){  
  this->beepDuration = duration_ms/16;
  this->beepTim = this->beepDuration;
  this->beepDurationDelay = delay_ms/16;
  this->beepCount = count*2-1;
  SOUND_PORT &= ~SOUND_PIN;
}

ISR(ADC_vect){
  if ((ADMUX & 1) == 1){
    thermoFan.tempConversion(ADCW);
  } else {
    solder.tempConversion(ADCW);
  }
  ADMUX ^= 1;
}
