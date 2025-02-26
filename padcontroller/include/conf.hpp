#pragma once
#include <stdbool.h>
// this file should be use to define configuration definitions
#define TX_PIN 0 // used as the interrupt pin

#define DBG true // debug macro

#define SPRINT 0b11000000
#define WALK1  0b10100000 // i can't figure a clever way to look for this
#define MIN_PIN 2
#define MAX_PIN MIN_PIN+3

#define THRESHOLD 550
#define STRSIZE 100


#define RED_LED 10
#define BLUE_LED 11
#define GREEN_LED 12
#define YELLOW_LED 13

#define bp breakpoint
