#pragma once // header guard

#include <Arduino.h>
#include <Keyboard.h>

using namespace std;
int updateState();

struct pinstruct{
    byte pins;
    bool toggleCrouch;
}; 

// helper struct just so i don't have to deal with passing around a char*
struct twoChar{
    char c1;
    char c2;
};

twoChar readableAnalogPin(int);
// byte arrToByte(int arr[8]); // only up to 8 bits stored,
                            // not checking crouch
void breakpoint();


