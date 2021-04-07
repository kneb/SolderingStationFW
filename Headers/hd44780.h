/*
 * hd44780.h
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */ 

#ifndef HD44780_H_
#define HD44780_H_

#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#define LCD_CUR_UL 0x0e
#define LCD_CUR_BS 0x0d
#define LCD_CUR_OFF 0x0c

class HD44780{
  private:
    void send(bool isCommand, uint8_t data);
    void switchE();
  public:
    HD44780();
    void init();
    void sendCommand(uint8_t cmd);
    void sendChar(const char chr);
    void sendString(const char* str);
    void clear();
    void goTo(uint8_t x, uint8_t y);
};




#endif /* HD44780_H_ */