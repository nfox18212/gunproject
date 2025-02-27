
#include <main.hpp>
#include <conf.hpp>
#include <util.hpp>



// put function declarations here:


// byte pinStates = 0b00000000; // why do i need to do this as a byte?
// first two bits are the two forward parts of the pad

// static bool toggleSprint = false;

int apinArray[10] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};

volatile bool continueBreakpoint = true; 

void isr_exitBP(void){
  continueBreakpoint = false;
  
  digitalWrite(GREEN_LED, HIGH); // signify that we're in an ISR
  // stalling for loop
  
  Serial.println("INSIDE isr_EXITBP");
  delayMicroseconds(10000); // wait for a while

  digitalWrite(GREEN_LED, LOW);

}
                 

void setup()
{
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);

  delay(1000);

  pinMode(3, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);

  pinMode(TX_PIN, INPUT);

  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // define set states for LEDs
  digitalWrite(15, LOW); 
  digitalWrite(14, LOW);
  digitalWrite(16, LOW);
  digitalWrite(10, LOW); // to see if program is active


  // set up breakpoint ISR
  attachInterrupt(digitalPinToInterrupt(0), isr_exitBP, RISING);

  
  Serial.println("STARTING PROGRAM!!!");

  // breakpoint2();
}

void loop()
{
  // put your main code here, to run repeatedly:
  Serial.println("AWOOGA");
  bp();
  int states = updateState();
  char fstr[STRSIZE];
  int pinVal = analogRead(A0);
   
  int f = snprintf(fstr, STRSIZE, "State is: %i, value of A0 is: %i\n", states, pinVal);
  if( f >= 0 && f < STRSIZE){
    Serial.print(fstr);
  }

  // bp();

  // delay(100);

  char sendKey = '\0'; // default to null, this will be the key the arduino sends
  // char modifierKeys[] = "none"; // will be important for sprinting, not needed r  /* determine what key to send

  switch (states){
    case 0b10100000:
    case 0b01010000:
    case 0b10010000:
    case 0b01100000:
      // look for walk input
      sendKey = 'w';                            
      break;
    case 0b1:
      sendKey = 'a'; // test input to send
      break;
    default:
      sendKey = '\0'; // if input combo is wrong, send a null for now
  }

  // TX_PIN is pullup pin on button
  if(digitalRead(7) == HIGH){

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
  // 10 pins read, max of 9
  for (int pindex = 9; pindex > -1; pindex--){
    int pin = apinArray[pindex];
    int aVal = analogRead(pin); // grab the value of the current pin
    // bitshift to store pin states in one integer
    state = state >> 1; 
    // twoChar twoCharPin = readableAnalogPin(pin);

    // 600 is the default threshold value, configured in conf.hpp
    if (aVal > THRESHOLD){
      state += 1;
    } else {
      state += 0; // i know this does nothing, its there just for clarity
    }    
    // shitty breakpoint
    // breakpoint();
  }

  return state;
}

