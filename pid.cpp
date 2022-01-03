/*
 * globals.cpp
 *
 * Created: 09.02.2021 13:59:12
 *  Author: Neb Konstantin Viktorovich
 */

#include "Headers/pid.h"
#include <avr/pgmspace.h>

PIDRegulator::PIDRegulator(){
  this->integral = 0.;
  this->prevError = 0;
  this->setMultipliers(0., 0., 0.);
  this->dT = 0.2;
}

void PIDRegulator::setMultipliers(float mP, float mI, float mD){
  this->kP = mP;
  this->kI = mI;
  this->kD = mD;
}

uint8_t PIDRegulator::computePower(uint16_t input, uint16_t set){
  int16_t error = set - input;
  this->integral = this->integral + error * this->dT * this->kI;
  if (this->integral > 100){ this->integral = 100.;}
  if (this->integral < 0){ this->integral = 0.;}
  float diff = (error - prevError) / this->dT;
  this->prevError = error;
  int16_t result = error * this->kP + this->integral + diff * this->kD;
  if (result > 100) { result = 100;}
  if (result < 0) { result = 0;}
  return result;
}

void PIDRegulator::clear(){
  this->integral = 0;
  this->prevError = 0;
}