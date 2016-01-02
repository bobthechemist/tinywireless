/*
  bobsrxtx.h - Library to assist with transiever applications
  Written by BoB LeSuer, 2016
  This code is public domain
  
*/
#ifndef bobsrxtx_h
#define bobsrxtx_h

#include "Arduino.h"

struct packet
{
  uint8_t counter;  // shoud this be a uint8_t? do I care about 2^15 iterations?
  uint8_t  id; // ID number, allowing for 256 transmitters to be addressed
  unsigned int sense1; // Value of sensor on pin 7 (A1)
  unsigned int sense2; // Value of sensor on pin 3 (A2)
  unsigned int sense3; // Value of sensor on pin 2 (A3)
}; 

// Variables to check for packet loss
struct packet_info {
  boolean started = false;
  uint8_t last = 0;
  int numlost = 0;
  float percentage = 100.;
};

void packet_status( packet_info &p, uint8_t counter );
  

// Return packet loss information

// Connect status LED to pin 3 of the ATTiny85
#ifndef STATUSLED
#define STATUSLED 1
#endif
#ifndef STATUSDELAY
#define STATUSDELAY 200
#endif
 
//Removing to minimize program size (not working anyway)
//void statusBlink(int pin, int num);

#endif
