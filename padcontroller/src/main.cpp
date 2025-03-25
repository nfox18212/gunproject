
#include <main.hpp>
#include <conf.hpp>
#include <util.hpp>

// put function declarations here:

// byte pinStates = 0b00000000; // why do i need to do this as a byte?
// first two bits are the two forward parts of the pad

// static bool toggleSprint = false;

// A6 = D4, A7 = D6, A8 = D8, A9 = D9
int apinArray[10] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9};

// volatile bool continueBreakpoint = true;

// void isr_exitBP(void){
//   continueBreakpoint = false;

//   digitalWrite(GREEN_LED, HIGH); // signify that we're in an ISR
//   // stalling for loop

//   Serial.println("INSIDE isr_EXITBP");
//   delayMicroseconds(10000); // wait for a while

//   digitalWrite(GREEN_LED, LOW);

// }

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
    if (f >= 0 && f < STRSIZE)
    {
        Serial.println(fstr);
    }

    delay(100); // adjust for sensitivity when polling

    char sendKey = '\0'; // default to null, this will be the key the arduino sends
    // char modifierKeys[] = "none"; // will be important for sprinting, not needed right now
    /* determine what key to send */

    switch (states)
    {
    // these are currently magic numbers, make documentation to describe
    // TODO: Finish this switch statement and replace the magic numbers with 
    case 0x00A0: // 0b 0000 0000 0101 0000 
    case 0x0050: // 0b 0000 0000 0011 0000
    case 0x0090: // 0b 0000 0000 1001 0000
    case 0x0060: // 0b 0000 0000 0110 0000
        // look for walk input
        sendKey = 'w';
        break;
    case 0x0001:
        sendKey = 'a'; // test input to send
        break;
    default:
        sendKey = '\0'; // if input combo is wrong, send a null for now
    }

    // switch
    if (digitalRead(7) == HIGH)
    {

        digitalWrite(13, HIGH);
        Serial.println("WRITING OUTPUT");
        Keyboard.begin(KeyboardLayout_en_US);
        Keyboard.write(sendKey);
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
