
#include <main.hpp>
#include <conf.hpp>
#include <util.hpp>
// #include <Joystick.h>

// static bool toggleSprint = false;

// A6 = D4, A7 = D6, A8 = D8, A9 = D9
int apinArray[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A10}; // change because the wire broke in A9
bool toggleSprint = false;
bool toggleCrouch = false;


int timer = 0; // used to display time in since program started

// heaviest cell


void setup()
{
    Serial.begin(9600);
    pinMode(TX_PIN, INPUT); // if high then it means keyboard transmission is enabled
    pinMode(LED_ZERO, OUTPUT); 
    pinMode(LED_ONE, OUTPUT);
    pinMode(LED_TWO, OUTPUT);
    pinMode(LED_THREE, OUTPUT);
    pinMode(LED_FOUR, OUTPUT);
    pinMode(A10, INPUT); // debugging pin
    pinMode(HALT_PIN, INPUT_PULLUP);

    
    // 0x0C is form feed/new page, clear the serial terminal from all the BLOCKING messages
    Serial.write(0xC);
    // Serial.println("STARTING PROGRAM!!!");
    delay(1000); 
}

void loop()
{
    while(digitalRead(HALT_PIN) == HIGH);

    timer += 1;
    // Serial.println("LOOPING");
    // put your main code here, to run repeatedly:
    
    int states = updateState();
    char fstr[STRSIZE];
    

    int f = snprintf(fstr, STRSIZE, "[MAIN] State is: %#4x, time is: %4i" , states, timer);
    if (f >= 0 && f < STRSIZE)
    {
      Serial.println(fstr);
    }

    char sendKey  = '\0'; // default to null, this will be the key the arduino sends
    char strafeKey = '\0'; // default to null, used for strafing
    bool strafing = false;    

    // exclusively to over-write state when debugging keyboard input
    if(digitalRead(2) == HIGH){
      sendKey = '?'; // should be impossible under normal circumstances
    }

    delay(100); // adjust for sensitivity when polling



    switch (states)
    {
    // docs.md explains this switch statement
  
    case WALK1:
    case WALK2:
    case WALK3:
    case WALK4:
      // look for walk input
      sendKey = 'w';
      break;
    case SPRINT:
      // combination of shift and w
      toggleSprint = !toggleSprint; // invert toggle crouch
      break;
    case TOG_CROUCH:
      toggleCrouch = !toggleCrouch;
      break;
    case RIGHT1:
    case RIGHT2:
      sendKey = 'd';
      break;
    case LEFT1:
    case LEFT2:
      sendKey = 'a';
      break;
    case STRAFE_L1:
    case STRAFE_L2:
      sendKey = 'w';
      strafeKey = 'a';
      strafing = true;
      break;
    case STRAFE_R1:
    case STRAFE_R2:
      sendKey = 'w';
      strafeKey = 'd';
      strafing = true;
      break;
    case BACKWARDS1:
    case BACKWARDS2:
    case BACKWARDS3:
    case BACKWARDS4:
    case BACKWARDS5:
      sendKey = 's';
      break;
    case STAYSTILL:
      sendKey = '\0';
      break;
    case JUMP:
      sendKey = ' ';
      break;
    default:
        sendKey = '\0'; // if input combo is wrong or user is standing in the middle, send a null for now
    }

    // for debugging, allows me to turn sending keyboard input off
    if (digitalRead(TX_PIN) == HIGH)
    {
        digitalWrite(TX_LED, HIGH); // show that keyboard output will be written
        Serial.println("WRITING OUTPUT");
        Keyboard.begin(KeyboardLayout_en_US);

        if (toggleCrouch){
          Keyboard.press(KEY_LEFT_CTRL);
        } else {
          Keyboard.release(KEY_LEFT_CTRL);
        }

        if (toggleSprint){
          Keyboard.press(KEY_LEFT_SHIFT);
        } else {
          Keyboard.release(KEY_LEFT_SHIFT);
        }

        if (strafing){
          Keyboard.press(strafeKey);
        }

        Keyboard.press(sendKey);
        delay(50);
        Keyboard.release(sendKey);
        Keyboard.release(strafeKey);
        
        Keyboard.end();
    }
    else
    {
        digitalWrite(TX_LED, LOW);
    }

    // Serial.write(0x0C); // new page   
}

int updateState()
{

    // using A0 - A8 and A10
    int state = 0;
    int heaviest_cell[2] = {NA, 0}; // i can brute force this array into a really shitty tuple
    // represents the cell ID and the analogue value of the current heaviest pin
    // 10 pins read, max of 9 - update to go to 10 to display A11 which should be D12
    for (int pindex = 9; pindex > -1; pindex--)
    {
        int pin = apinArray[pindex];
        int aVal = analogRead(pin); // weight upon the current cell
        // bitshift to store pin states in one integer
        state = state << 1; // LEFT SHIFT LEFT SHIFT LEFT SHIFT
        twoChar twoCharPin = readableAnalogPin(pin);
        char str[STRSIZE];

        if(heaviest_cell[1] < aVal){
          // if there is a heavier weight upon the previous recorded weight, update the new cell
          heaviest_cell[0] = pindex; // current pin we're looking at
          heaviest_cell[1] = aVal; // new weight 
        }

        // 600 is the default threshold value, configured in conf.hpp
        if (aVal > THRESHOLD)
        {
            state += 1;
        }
        else
        {
            state += 0; // i know this does nothing, its there just for clarity
        }

        snprintf(str, 100, "%c%c reads %.4i.  Therefore, state is: %#.4x", twoCharPin.c1, twoCharPin.c2, aVal, state);
        Serial.println(str);
    }

    // if the heaviest cell is actually something interesting, display it on the LEDs
    if (heaviest_cell[0] != NA){

      // LOW is defined as 0, HIGH defined as 1.  We can avoid uncessesary if statements by using 
      // a bitwise AND for what to write in digitalWrite()
      digitalWrite(LED_ZERO, heaviest_cell[0] & 1); // 2^0
      digitalWrite(LED_ONE, heaviest_cell[0] & 2); // 2^1
      digitalWrite(LED_TWO, heaviest_cell[0] & 4); // 2^2
      digitalWrite(LED_THREE, heaviest_cell[0] & 8); // 2^3
      digitalWrite(LED_FOUR, heaviest_cell[0] & 16); // 2$4


      // this will write out the number of the heaviest cell in binary
    }

    return state;
}
