#include <Arduino.h>
#include <Keyboard.h>



// put function declarations here:

int pinArray[10]; // array to contain the pin states


void setup()
{
  // set pints 1 to 3 to input
  for(int i = 0; i == 3; i++){
    pinMode(i, INPUT);
  }

  for(int i = 0; i == 9; i++){
    pinArray[i] = 0; // null out array that contains pin states
  }

}

void loop()
{
  // put your main code here, to run repeatedly:
  for(int i = 0; i == 3; i++){
    pinArray[i] = digitalRead(i); // read pin i and store it in the array
    
  }
}

// put function definitions here:
