#pragma once // header guard

using namespace std;
void int_ToggleSendInputs(); // ISR to toggle sending keyboard inputs


struct {
    byte pins = 0;
    bool toggleCrouch = 0;
} pinarr;

byte arrToByte(int arr[8]); // only up to 8 bits stored,
                            // not checking crouch