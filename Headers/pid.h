/*
 * globals.h
 *
 * Created: 09.02.2021 13:58:42
 *  Author: Neb Konstantin Viktorovich
 */

#ifndef PID_H_
#define PID_H_

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

class PIDRegulator{
  private:
    float kP;
    float kI;
    float kD;
    float dT;
    float integral;
    int16_t prevError;
  public:
    PIDRegulator();
    void setMultipliers(float mP, float mI, float mD);
    uint8_t computePower(uint16_t input, uint16_t set);
    void clear();
};

#endif /* PID_H_ */