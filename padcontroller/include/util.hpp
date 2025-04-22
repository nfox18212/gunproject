#pragma once
#include <stdbool.h>

/* 
* General purpose utility and debugging file
*/

extern volatile bool continueBreakpoint;

// helper struct just so i don't have to deal with passing around a char*
struct twoChar{
    char c1;
    char c2;
};

twoChar readableAnalogPin(int);
// byte arrToByte(int arr[8]); // only up to 8 bits stored,
                            // not checking crouch

void breakpoint();

void breakpoint2();