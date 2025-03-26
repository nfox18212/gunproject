
#include <main.hpp>
#include <conf.hpp>
#include <util.hpp>

// put function declarations here:

// byte pinStates = 0b00000000; // why do i need to do this as a byte?
// first two bits are the two forward parts of the pad

// static bool toggleSprint = false;

// A6 = D4, A7 = D6, A8 = D8, A9 = D9
int apinArray[10] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};
bool toggleSprint = false;
bool toggleCrouch = false;


void setup()
{
    Serial.begin(9600);
    pinMode(3, INPUT_PULLUP);
    pinMode(5, INPUT_PULLUP);
    pinMode(TX_PIN, INPUT_PULLUP);

    pinMode(YELLOW_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // define set states for LEDs
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH); // to see if program is active

    // set up breakpoint ISR
    // attachInterrupt(digitalPinToInterrupt(0), isr_exitBP, RISING); // wasn't working, don't know why, not dealing with it

    delay(1000);

    // TODO: Finish this switch statement and replace the magic numbers with variables
    // blocking while loop
    while (digitalRead(0) != LOW)
    {
        Serial.println("BLOCKING");
    }
    // 0x0C is form feed/new page, clear the serial terminal from all the BLOCKING messages
    Serial.write(0xC);
    Serial.println("STARTING PROGRAM!!!");
    delay(1000); //-
}

void loop()
{
    Serial.println("LOOPING");
    // put your main code here, to run repeatedly:
    int states = updateState();
    char fstr[STRSIZE];
    int pinVal = analogRead(A0);

    int f = snprintf(fstr, STRSIZE, "State is: %#4x, value of A0 is: %4i", states, pinVal);
    if (f >= 0 && f < STRSIZE)bool toggleSprint = false;
    {
        Serial.println(fstr);
    }

    // exclusively to over-write state when debugging keyboard input
    if(analogRead(A10) > THRESHOLD){
      states = 0xFFF; // should be impossible under normal circumstances
    }

    delay(100); // adjust for sensitivity when polling

    char sendKey  = '\0'; // default to null, this will be the key the arduino sends
    char strafeKey = '\0'; // default to null, used for strafing
    bool strafing = false;

    switch (states)
    {
    // docs.md explains shit
  
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
    case 0xFFF: // impossible under normal circumstances
        sendKey = '?'; // test input to send
        break;
    default:
        sendKey = '\0'; // if input combo is wrong, send a null for now
    }

    // for debugging, allows me to turn sending keyboard input off
    if (digitalRead(7) == HIGH)
    {
        digitalWrite(13, HIGH); // show that keyboard output will be written
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
        digitalWrite(13, LOW);
    }

    // Serial.write(0x0C); // new page
}

int updateState()
{

    // using A0 - A9
    int state = 0;
    // 10 pins read, max of 9
    for (int pindex = 9; pindex > -1; pindex--)
    {
        int pin = apinArray[pindex];
        int aVal = analogRead(pin); // grab the value of the current pin
        // bitshift to store pin states in one integer
        state = state << 1; // LEFT SHIFT LEFT SHIFT LEFT SHIFT
        twoChar twoCharPin = readableAnalogPin(pin);
        char str[STRSIZE];

        // 600 is the default threshold value, configured in conf.hpp
        if (aVal > THRESHOLD)
        {
            state += 1;
        }
        else
        {
            state += 0; // i know this does nothing, its there just for clarity
        }

        snprintf(str, 100, "%c%c reads %.4i.  Therefore, state is: %.4x", twoCharPin.c1, twoCharPin.c2, aVal, state);
        Serial.println(str);
    }

    return state;
}
