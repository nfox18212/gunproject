#pragma once // header guard

using namespace std;
void int_ToggleSendInputs(); // ISR to toggle sending keyboard inputs


struct pinstruct{
    byte pins;
    bool toggleCrouch;
}; 

// byte arrToByte(int arr[8]); // only up to 8 bits stored,
                            // not checking crouch