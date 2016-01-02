/* 
 *  Demonstration of RF communication between Arduino Uno
 *  and an ATTiny85 using the XD-RF-5V and XD-FST wireless
 *  receiver/transmitters.
 *  
 *  Uses the RadioHead library: http://www.airspayce.com/mikem/arduino/RadioHead/
 *  with modifications of the example code provided therein.
 *  Includes data transfer ideas mentioned by swe-dude in the 
 *  Arduino forums: https://forum.arduino.cc/index.php?topic=313587.0
 *  
 *  This code is public domain.
 *  
 *  Receiver code intended to be run on the Arduino Uno.  RF reciever
 *  (XD-RF-5V) data pin connected to pin 11.
 *  
 *  Version 2 -
 *  - Implement counter check
 *  
 */
#include <RH_ASK.h>
#define rxcode
#include <bobsrxtx.h>

// Default settings for speed, rx, tx, en, inv explicitly stated
RH_ASK driver(2000,11,12,10,false);


/*
 
// It is **CRITICAL** that the receiver and transmitter code use the same struct
struct packet
{
  // Naturally, additional types can be added here
  int counter;
} data;
*/

packet data;
packet_info pinfo;

long t;

void setup() 
{
  // Output will be sent to the serial monitor.
  Serial.begin(9600);
  if (!driver.init()){Serial.println("Driver init. failed.");}
  else {Serial.println("Driver initialized.");}
  t = millis();
}

void loop() 
{
  // Create temporary space for data
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);

  // If data are received, copy it into the data structure
  // and print the counter to the serial line.
  if (driver.recv(buf,&buflen))
  {
    memcpy(&data,buf,sizeof(data));
    Serial.print(data.id);
    Serial.print(",");
    Serial.print(data.sense1);
    Serial.print(",");
    Serial.print(data.sense2);
    Serial.print(",");
    Serial.print(data.sense3);
    Serial.print(",");
    Serial.print(millis()-t);
    Serial.println("");
    t = millis();
    packet_status(pinfo, data.counter);      
      
  }
}
