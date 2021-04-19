/*
 * lcd.h
 *
 * Created: 07.04.2021 15:33:01
 *  Author: Neb Konstantin Viktorovich
 */ 


#ifndef LCD_H_
#define LCD_H_

struct Menu{
  uint8_t isEdit;
  uint8_t param;
  uint8_t level;
};

class Lcd{
  private:
  public:
    Lcd();
    Menu menu;
    void printMain();
    void printLogo();
    void changeParam(bool isClockwise);
    void printIconsStatus();
};

void itoa(char* buf, uint16_t source, uint8_t lenZero);

#endif /* LCD_H_ */