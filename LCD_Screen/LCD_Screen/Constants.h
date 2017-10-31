#pragma once

#ifndef _CONSTANTS_h
#define _CONSTANTS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//Ultrasonic Sensor
const int Button_1 = 13;
const int Button_2 = 12;
const int Button_3 = 11;

// RGB LEDs
const int Red_Led    = 10;
const int Green_Led  = 9;
const int Yellow_Led = 8;



#endif