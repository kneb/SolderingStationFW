/*
 * lcd.h
 *
 * Created: 07.04.2021 15:33:01
 *  Author: Neb Konstantin Viktorovich
 */ 

#ifndef LCD_H_
#define LCD_H_

#define CURSOR_TYPE_EMPTY 0x20
#define CURSOR_TYPE_ARROW 0

#define CURSOR_LEFT_ARROW 0x7f
#define CURSOR_RIGHT_ARROW 0x7e
#define CURSOR_LEFT_ANGLE 0x3c
#define CURSOR_RIGHT_ANGLE 0x3e

#define ICON_RAISED_TFAN 0xc6
#define ICON_TFAN_ON_STAND 0x05

#define CALIBRATION_SOLDER 0x00
#define CALIBRATION_THERMOFAN 0x04

struct St_Menu {
  uint8_t isEdit;
  uint8_t param;
  uint8_t level;
};

class Lcd{
  private:
  public:
    Lcd();
    St_Menu menu;
    void printLogo();
    void printMain(); 
    void printMenu();
    void printPIDMenu();
    void printCalibration(uint8_t calibrationMenu);
    void printIconsStatus();
    void printMenuCursor(uint8_t cursorType);
    void printInt(uint8_t x, uint8_t y, uint16_t source, uint8_t len, bool zero=true);
    void swapIsEdit();
};

void itoa(char* buf, uint16_t source, uint8_t len, bool zero=true);

#endif /* LCD_H_ */