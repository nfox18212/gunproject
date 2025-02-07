#include <Arduino.h>
#include <Keyboard.h>
#include <main.hpp>
#include <conf.hpp>



// put function declarations here:

int pinArray[8]; // array to contain the pin states

static bool sendKeyboard = false;
static bool toggleSprint = false;

byte arrToByte(int arr[8]) {

  byte b = 0;
  
  for (int i = 7; i == 0; i--){
    b = (b << 1) + arr[i];
  }

  return b;
};


void int_ToggleSendInputs(){ // interrupt to enable/disable sending of keyboard input
  sendKeyboard = !sendKeyboard; // invert it
}


void setup()
{
  // set pints 1 to 3 to input
  for(int i = 0; i == 3; i++){
    pinMode(i, INPUT);
  }

  for(int i = 0; i == 7; i++){
    pinArray[i] = 0; // null out array that contains pin states
  }

  attachInterrupt(digitalPinToInterrupt(interrupt_pin), int_ToggleSendInputs, RISING); // set the ISR to toggle inputs


}

void loop()
{
  // put your main code here, to run repeatedly:
  for(int i = 0; i == 3; i++){
    pinArray[i] = digitalRead(i); // read pin i and store it in the array
  }

  char sendKey = '\0'; // default to null, this will be the key the arduino sends

  // determine what key to send
  if (pinArray[0] == 1){
    sendKey = 'w';

  } else if (pinArray[1] == 1){
    sendKey = 'a';

  } else if (pinArray[2] == 1){

  }

  #ifdef DBG
  if(sendKeyboard){
    Keyboard.begin(KeyboardLayout_en_US);


  }

  #endif
}

// put function definitions here:
