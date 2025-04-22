#include <Adafruit_seesaw.h>
#include <seesaw_neopixel.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <SPI.h>

#define DEFAULT_I2C_ADDR 0x3A


#define SECOND_I2C_ADDR 0x3B


#define SWITCH1 18  // PA01
#define SWITCH2 19  // PA02
#define SWITCH3 20  // PA03
#define SWITCH4 2   // PA06
#define PWM1 12     // PC00
#define PWM2 13     // PC01
#define PWM3 0      // PA04
#define PWM4 1      // PA05


const int triggerPin = 4;
const int triggerPin2 = 5;
Adafruit_seesaw ss;
Adafruit_seesaw ss2;

int triggerState = 0;  
int triggerState2 = 0; 

void setup() {
  Serial.begin(115200);

  //while (!Serial) delay(10);  // wait until serial port is opened

  Serial.println(F("Adafruit PID 5296 I2C QT 4x LED Arcade Buttons test!"));

  // Initialize seesaw
  if (!ss.begin(DEFAULT_I2C_ADDR)) {
    Serial.println(F("Seesaw not found!"));
    while (1) delay(10);  // Stop if seesaw is not found
  }

  if (!ss2.begin(SECOND_I2C_ADDR)) {
    Serial.println(F("Seesaw not found!"));
    while (1) delay(10);  // Stop if seesaw is not found
  }

  uint16_t pid;
  uint8_t year, mon, day;

  ss.getProdDatecode(&pid, &year, &mon, &day);
  Serial.print("Seesaw found PID: ");
  Serial.print(pid);
  Serial.print(" Datecode: ");
  Serial.print(2000 + year); Serial.print("/");
  Serial.print(mon); Serial.print("/");
  Serial.println(day);

  if (pid != 5296) {
    Serial.println(F("Wrong seesaw PID"));
    while (1) delay(10);  // Stop if wrong PID
  }

  Serial.println(F("Seesaw started OK!"));

  // Set pin modes
  ss.pinMode(SWITCH1, INPUT_PULLUP);
  ss.pinMode(SWITCH2, INPUT_PULLUP);
  ss.pinMode(SWITCH3, INPUT_PULLUP);
  ss.pinMode(SWITCH4, INPUT_PULLUP);

  ss2.pinMode(SWITCH1, INPUT_PULLUP);
  ss2.pinMode(SWITCH2, INPUT_PULLUP);
  ss2.pinMode(SWITCH3, INPUT_PULLUP);
  ss2.pinMode(SWITCH4, INPUT_PULLUP);

  pinMode(triggerPin, INPUT_PULLUP);
  // Initialize PWM pins with a default value 127
  ss.analogWrite(PWM1, 0);
  ss.analogWrite(PWM2, 0);
  ss.analogWrite(PWM3, 0);
  ss.analogWrite(PWM4, 0);

  ss2.analogWrite(PWM1, 0);
  ss2.analogWrite(PWM2, 0);
  ss2.analogWrite(PWM3, 0);
  ss2.analogWrite(PWM4, 0);

  // Start Keyboard library
  Keyboard.begin();
}

//uint8_t incr = 0;

void loop() {
  // Check button press and handle accordingly
  if (!ss.digitalRead(SWITCH1)) { //WHITE
    Serial.println("Switch 1 pressed");
    
    Keyboard.press('e');

    ss.analogWrite(PWM1, 255);
    //incr += 255;  // Increase PWM value
    
    delay(100);  // Debounce delay
    digitalWrite(triggerPin, HIGH);  
    digitalWrite(triggerPin2, HIGH); 


    while (!ss.digitalRead(SWITCH1)) { 

        //checks for switch 2
        triggerState = digitalRead(triggerPin);

        if (triggerState == LOW) { 
            Keyboard.press(KEY_UP_ARROW); 
        } else {
            Keyboard.release(KEY_UP_ARROW); 
        }
        

        triggerState2 = digitalRead(triggerPin2);
        //checks for switch 3
        if (triggerState2 == LOW) { 
            Keyboard.press(KEY_DOWN_ARROW);  
        } else {
            Keyboard.release(KEY_DOWN_ARROW); 
        }

        delay(50); 
    }
    Keyboard.release('e');  
    ss.analogWrite(PWM1, 0);  // Turn off PWM
  }



  if (!ss.digitalRead(SWITCH2)) {
    Serial.println("Switch 2 pressed");

    
    Keyboard.press('r');  
    ss.analogWrite(PWM2, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('r');
    ss.analogWrite(PWM2, 0);
  }

  if (!ss.digitalRead(SWITCH3)) {
    Serial.println("Switch 3 pressed");
    Keyboard.press('f');  // Send 'c' key
   
    ss.analogWrite(PWM3, 255);
    //incr += 225;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('f');
    ss.analogWrite(PWM3, 0);
  }


  if (!ss.digitalRead(SWITCH4)) {
    Serial.println("Switch 4 pressed");
    Keyboard.press('4');  // Send 'd' key
    ss.analogWrite(PWM4, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('4');
    ss.analogWrite(PWM4, 0);
  }
  /////////////////////////////////////////////////////////////////////
  //                                                                 //
  //                                                                 //
  //                                                                 //
  //                                                                 //
  //                                                                 //
  /////////////////////////////////////////////////////////////////////

  // second breakout board WYWG
  if (!ss2.digitalRead(SWITCH1)) {
    Serial.println("Switch 1 pressed");
    Keyboard.press('3');  
    ss2.analogWrite(PWM1, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('3');
    ss2.analogWrite(PWM1, 0);
  }

  if (!ss2.digitalRead(SWITCH2)) {
    Serial.println("Switch 2 pressed");
    Keyboard.press('2');  
    ss2.analogWrite(PWM2, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('2');
    ss2.analogWrite(PWM2, 0);
  }

  if (!ss2.digitalRead(SWITCH3)) {
    Serial.println("Switch 3 pressed");
    Keyboard.press('1');  
    ss2.analogWrite(PWM3, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('1');
    ss2.analogWrite(PWM3, 0);
  }

  if (!ss2.digitalRead(SWITCH4)) { //green
    Serial.println("Switch 4 pressed");
    Keyboard.press('q');  
    ss2.analogWrite(PWM4, 255);
    //incr += 255;
    delay(100);  // Debounce delay
  } else {
    Keyboard.release('q');
    ss2.analogWrite(PWM4, 0);
  }

  triggerState = digitalRead(triggerPin);
  if (triggerState == LOW) {          // Trigger is pressed
    Mouse.press(MOUSE_LEFT);          // Simulate left mouse click
  } else {                            // Trigger is released
    Mouse.release(MOUSE_LEFT);        // Release left mouse click
  }

  triggerState2 = digitalRead(triggerPin2);
  if (triggerState2 == LOW) {          // Trigger is pressed
    Mouse.press(MOUSE_RIGHT);          // Simulate left mouse click
  } else {                            // Trigger is released
    Mouse.release(MOUSE_RIGHT);        // Release left mouse click
  }

  delay(10); // Debounce delay


  delay(50);  // Add a small delay to avoid spamming
}