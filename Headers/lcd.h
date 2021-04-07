/*
 * lcd.h
 *
 * Created: 07.04.2021 15:33:01
 *  Author: Neb Konstantin Viktorovich
 */ 


#ifndef LCD_H_
#define LCD_H_

class Menu{
  private:
  public:
  Menu();
    uint8_t isEdit;
    uint8_t param;
    uint8_t level;
};

class Lcd{
  private:
  public:
    Menu menu;
    void printMain();
    void printLogo();
};


#endif /* LCD_H_ */