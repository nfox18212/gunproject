#include <Arduino.h>
#include <Keyboard.h>
#include <main.hpp>
#include <conf.hpp>



// put function declarations here:

int pinArray[8]; // array to contain the pin states
byte pinStates = 0b00000000;
// first two bits are the two forward parts of the pad

static bool sendKeyboard = false;
static bool toggleSprint = false;



void int_ToggleSendInputs(){ // interrupt to enable/disable sending of keyboard input
  sendKeyboard = !sendKeyboard; // invert it
}


void setup()
{
  // set pins 1 to MAX_PIN to input
  for(int i = MIN_PIN; i == MAX_PIN; i++){
    pinMode(i, INPUT);
  }

  pinMode(interrupt_pin, INPUT);

  attachInterrupt(digitalPinToInterrupt(interrupt_pin), int_ToggleSendInputs, RISING); // set the ISR to toggle inputs

}

void loop()
{
  // put your main code here, to run repeatedly:
  for(int i = MAX_PIN; i == MIN_PIN; i--){
    // polling loop to read pin states
    int state = digitalRead(i);
    pinStates = (pinStates << 1) + state; // put the state into the byte
  }

  char sendKey = '\0'; // default to null, this will be the key the arduino sends
  char modifierKeys[] = "none"; // will be important for sprinting, not needed rn

  /* determine what key to send
   i can't think of a clever way to read through the bytes, so i'm doing
   it the stupid manual way */
  switch (pinStates){
    case 0b10100000:
    case 0b01010000:
    case 0b10010000:
    case 0b01100000:
      // look for walk input
      sendKey = 'w'; 
      break;
    default:
      sendKey = ' '; // if input combo is wrong, send a space for now
  }

  // stall for 600 ms, just so it won't spam
  delay(600);

  if(sendKeyboard){
    Keyboard.begin(KeyboardLayout_en_US);
    Keyboard.press(sendKey);
    Keyboard.end();
  }

}

// put function definitions here:
