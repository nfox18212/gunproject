# Movement Pad Documentation

## Important Parts
- Force Sensitive Resistors, a form of potentiometer that changes resistance with applied pressure.  Purchased from [ddrpad.com](https://ddrpad.com/collections/fsr-sensors/products/force-sensitive-resistor-fsr-sensor-square-interlink?variant=39251885817908)
- Arduino Leonardo, as it supports the keyboard library.  
- Ten 430 Ohm resistors.  The value of the resistor is important because the lower the resistance, the lower the voltage received by the Arduino.  
- Roughly 36 feet of wire are used, running underneath the pad
## Input Scanning 
The code scans through all 10 FSRs, and stores the state in an integer intended to be read in binary or hex.   If the analogue input of the FSR is above a specific threshold, defined in [conf.hpp](../include/conf.hpp). The number has a total of 10 bits that can change, the 10th bit corresponding to the FSR connected to A9, and the 1st bit corresponds to A0.  Below is a diagram that shows what FSR corresponds to what panel on the board, where the top of the diagram is front of the movement pad. There is also markings identifying what each cell is below the acrylic panels and on the underside of the pad.  

Additionally, cell has a red wire that corresponds to the Arduino Leonardo's data pin for that cell.  For example, there is a red wire labeled with number on some masking tape that says it is from Cell 8.  Therefore, it must go to A8.  All the white wires go to the positive voltage line.  This can be either the Arduino or a separate battery like the 12 Volt Dewalt battery.

Unfortunately, there are only 6 analogue pins that are labeled on the Arduino Leonardo even through it supports up to 12 analogue inputs.  This is because some of the digital ports double as analogue ports. Specifically, [digital pin 4 is A6, pin 6 is A7, pin 8 is A8, pin 9 is A9, pin 10 is A10 and pin 12 is A11](https://www.arduino.cc/reference/tr/language/functions/analog-io/analogread/).  Only pins 4 to 9 are used<sup>1</sup>.

1: **ADDENDUM:**  Due to the wire breaking inside of Pin 9, Cell 9 has been moved to port 10/A10.  

![image](Screenshot_20250325_215637.png)

## Configuration
Basic configuration can be done in [conf.hpp](../include/conf.hpp).  The threshold value can be configured, and the cells needed to cause a specific action can be changed as well within the define statements.   The code is mostly device agnostic as well.  To define a new device to compile the code to will require updating the [platformio.ini file](../platformio.ini).  This document will not discuss the myriad options provided by Platformio, but you can find that [here.](https://docs.platformio.org/en/latest/)

Additionally, the screwed-in pieces of wood that rest on top of the acrylic panels can be adjusted by screwing in or out the screw.  This can prevent false positives from the wood pushing down the acrylic too tightly.  Changing the threshold can also help.

## Usage



## Common Problems
- Ghost inputs may be caused by the 
