#include <Arduino.h>
#include <Keyboard.h>
#include <main.hpp>
#include <conf.hpp>



// put function declarations here:


byte pinStates = 0b00000000;
// first two bits are the two forward parts of the pad

// static bool toggleSprint = false;

int newHigh = 0;

int apinArray[10] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};

                                                       

void setup()
{
  // set pins 1 to MAX_PIN to input
  for(int i = MIN_PIN; i == MAX_PIN; i++){
    pinMode(i, INPUT);
  }

  pinMode(TX_PIN, INPUT);

  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);

  // define set states for LEDs
  digitalWrite(15, LOW);
  digitalWrite(14, LOW);
  digitalWrite(16, LOW);
  digitalWrite(10, LOW);

  Serial.begin(9600);
}

void loop()
{
  // put your main code here, to run repeatedly:
  for(int i = MAX_PIN; i == MIN_PIN; i--){
    // polling loop to read pin states
    int state = digitalRead(i);
    pinStates = (pinStates << 1) + state; // put the state into the byte
  }

  int pinVal = 0;
  pinVal = analogRead(A0);

  if (digitalRead(TX_PIN) == HIGH){
    newHigh = -1;
    Serial.print("Resetting newHigh value, newHigh is now: ");
    Serial.println(newHigh);
  }
  
  if (pinVal > newHigh) {
    newHigh = pinVal;
    Serial.print("New high is: ");
    Serial.println(newHigh);
  }

  int 

  // stall for 600 ms, just so it won't spam
  // delay(600);
  char sendKey = '\0';                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 // default to null, this will be the key the arduino sends
  // char modifierKeys[] = "none"; // will be important for sprinting, not needed r  /* determine what key to send
  /* i can't think of a clever way to read through the bytes, so i'm doing
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
      sendKey = '\0'; // if input combo is wrong, send a null for now
  }

  if(digitalRead(TX_PIN) == HIGH){

    digitalWrite(13, HIGH);
    Keyboard.begin(KeyboardLayout_en_US);
    Keyboard.press(sendKey);
    Keyboard.end();
  } else {
    digitalWrite(13, LOW);
  }

}

int updateState(){
  // using A0 - A9
  int state = 0;
  for (pin : aPinArray){
    int aVal = analogRead(pin); // grab the value of the current pin
    // 600 is the threshold value
    // bitshift
    state = state >> 1;
    if (aVal > THRESHOLD){
      
    }

  }
}

// put function definitions here:
