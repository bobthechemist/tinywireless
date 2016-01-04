# tinywireless
Remote sensing with an ATTiny85 and cheap RF transmitter/receiver
## Introduction
My first attempt at creating a remote sensing platform based on RF communcation (using [RadioHead](http://www.airspayce.com/mikem/arduino/RadioHead/index.html), an ATTiny85 microcontroller for sensor reading and data transmission, and an Arduino Uno for data receiving/processing.
Note: this was a weekend project (that took longer than a weekend, but what can you say...) meant to teach me something about RF communication.  If you happen to stumble along this information, I hope you find it useful, but be aware that my purpose for posting the code is so I don't lose it, not that I think it is overly valuable to the world.
## Files
- *README.md* This file
- *tiny-tx-rh.ino* Code for the ATTiny85 to transmit readings from sensors on each of the 3 analog input pins
- *uno-rx-rh.ino* Code to receive data from the ATTiny85 on the Arduino Uno
- *bobsrxtx.cpp* Helper functions, most importantly the data struct used for the two microcontrollers
- *bobsrxtx.h* Header file for above.
## Updates
- 160103: Added routine to encrypt the data packet with an XOR cipher.  The two AVR files do not yet implement encryption
