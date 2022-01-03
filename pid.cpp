/*
 * globals.cpp
 *
 * Created: 09.02.2021 13:59:12
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/pid.h"
#include <avr/pgmspace.h>

PIDRegulator::PIDRegulator(){
  this->integral = 0;
  this->prevError = 0;
  this->setMultipliers(0., 0., 0.);
}

void PIDRegulator::setMultipliers(float mP, float mI, float mD){
  this->kP = mP;
  this->kI = mI;
  this->kD = mD;
}