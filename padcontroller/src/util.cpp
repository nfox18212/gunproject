#include <conf.hpp>
#include <util.hpp>
#include <Arduino.h>

#define c1 pin.c1
#define c2 pin.c2


twoChar readableAnalogPin(int index){

    twoChar pin;
    c1 = 'A';

    // yes i know this switch statement is gross leave me alone

    // converts the defined value of A0-A9 (18-27) to two character which is more readable when printed out to serial
    switch(index){
        case A0:
            c2 = '0';
            break;
        case A1:
            c2 = '1';
            break;
        case A2:
            c2 = '2';
            break;
        case A3:
            c2 = '3';
            break;
        case A4:
            c2 = '4';
            break;
        case A5:
            c2 = '5';
            break;
        case A6:
            c2 = '6';
            break;
        case A7:
            c2 = '7';
            break;
        case A8:
            c2 = '8';
            break;
        case A9:
            c2 = '9';
            break;
        case A10:
            c2 = 'A';
            break;
        default:
            c1 = 'N';
            c2 = 'P';
    }

    return pin;
};


/* 
    Implementing my own breakpoint sucks and I hate it
*/
// void breakpoint(){

//     // turn BLUE_LED on to show we've hit the breakpoint
//     digitalWrite(BLUE_LED, HIGH);
//     while(continueBreakpoint){
//         // try doing this stalling loop with an interrupt to exit instead
//         // if(digitalRead(6) == LOW){
//         //     break;
//         // }
//     }

//     // delay(100); // delay
//     // turn that led off to show we're leaving the breakpoint
//     digitalWrite(BLUE_LED, LOW);

//     continueBreakpoint = true;
    
//     return;
// }

// void breakpoint2(){
    
//     digitalWrite(RED_LED, HIGH);
    
//     while(digitalRead(5) == LOW){
//         Serial.println("STALL");
//     }

//     digitalWrite(RED_LED, LOW);

// }