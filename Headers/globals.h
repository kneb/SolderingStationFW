/*
 * globals.h
 *
 * Created: 09.02.2021 13:58:42
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "hd44780.h"
#include "lcd.h"
#include "encoder.h"
#include "thermofan.h"
#include "solder.h"

#define DDR_LCD_RS DDRD
#define PORT_LCD_RS PORTD
#define PIN_LCD_RS (1 << PIND0)
#define DDR_LCD_E DDRD
#define PORT_LCD_E PORTD
#define PIN_LCD_E (1 << PIND1)
#define DDR_LCD_D DDRD
#define PORT_LCD_D PORTD

#define DDR_ENCODER_SW DDRC
#define DDR_ENCODER_A DDRD
#define DDR_ENCODER_B DDRC
#define PIN_ENCEDER_SW PINC
#define ENCEDER_SW (1 << PINC4)

#define LED_PORT PORTB
#define LED_FEN (1 << PINB4) //led power termofen (0 - On, 1 - Off)
#define LED_SOL (1 << PINB5) //led power solder (0 - On, 1 - Off)

#define SOUND_PORT PORTB
#define SOUND_PIN 1


class Sound{
  private:
    uint8_t beepDuration;
    uint8_t beepDurationDelay;
    uint8_t beepCount;
    uint8_t beepTim;
  public:
    void beep(uint16_t duration_ms, uint8_t count, uint16_t delay_ms);
    void getBeep();
};

extern HD44780 hd44780;
extern Lcd lcd;
extern Encoder encoder;
extern ThermoFan thermoFan;
extern Solder solder;
extern Sound sound;

void init();

#endif /* GLOBALS_H_ */