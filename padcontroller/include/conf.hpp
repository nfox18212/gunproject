#pragma once
#include <stdbool.h>
// this file should be use to define configuration definitions
#define interrupt_pin 7 // used as the interrupt pin

#define DBG true // debug macro

#define SPRINT 0b11000000
#define WALK1  0b10100000 // i can't figure a clever way to look for this
#define MIN_PIN 0

#if DBG 
#define MAX_PIN 7
#else
#define MAX_PIN 7
#endif

