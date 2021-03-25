/*
 * solder.h
 *
 * Created: 07.02.2021 2:33:41
 *  Author: Neb Konstantin Viktorovich
 */


#ifndef SOLDER_H_
#define SOLDER_H_

#include <avr/io.h>

class Solder{
  private:
  public:
    Solder();
    uint16_t setTemp;
    uint16_t currentTemp;  
};

#endif /* SOLDER_H_ */