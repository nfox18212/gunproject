#pragma once
#include <stdbool.h>
// this file should be use to define configuration definitions
#define TX_PIN 0 // used as the interrupt pin

#define DBG true // debug macro

#define SPRINT      0x003 // sprint
#define WALK1       0x021 // clever way to do this is more annoying to do than the stupid way
#define WALK2       0x022
#define WALK3       0x041
#define WALK4       0x042
#define RIGHT1      0x0C0
#define RIGHT2      0x0A0
#define LEFT1       0x030
#define LEFT2       0x050
#define STRAFE_L1   0x012
#define STRAFE_L2   0x014
#define STRAFE_R1   0x082
#define STRAFE_R2   0x084
#define BACKWARDS1  0x300
#define BACKWARDS2  0x120
#define BACKWARDS3  0x140
#define BACKWARDS4  0x220
#define BACKWARDS5  0x240
#define STAYSTILL   0x060
#define TOG_CROUCH  0x009
#define JUMP        0x000
#define MIN_PIN 2
#define MAX_PIN MIN_PIN+3

#define THRESHOLD 600
#define STRSIZE 100


#define RED_LED 10
#define BLUE_LED 11
#define GREEN_LED 12
#define YELLOW_LED 13

#define bp breakpoint