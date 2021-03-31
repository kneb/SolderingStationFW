/*
 * thermofan.cpp
 *
 * Created: 05.02.2021 15:57:08
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/thermofan.h"

ThermoFan::ThermoFan(){
  this->fan = 98;
  this->setTemp = 250;
  this->currentTemp = 0;
}