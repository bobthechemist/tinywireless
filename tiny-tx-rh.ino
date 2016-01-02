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
 *  Transmitter code intended to be run on the ATTiny85.  RF transmitter
 *  (XD-FST) data pin connected to pin 2 and resistor/LED connected to pin 5.
 */
#include <RH_ASK.h>
#include <bobsrxtx.h>
// It looks like the ATTiny85 requires ~ 110 ms to read the three sensors and transmit
// that information wirelessly.
#define LOOPDELAY 1000

// It's possible that leaving the enable pin set to the 
// default value (10) will cause some problems, but I have
// not encountered them yet. The RX pin will be reassigned 
RH_ASK driver(2000,STATUSLED,0);


packet data;
byte buf[sizeof(data)]={0};

void setup()
{
  
  // LED probably won't light since it is assigned the RX pin
  //if (!driver.init()) { statusBlink(STATUSLED,5); }
  //else { statusBlink(STATUSLED,1); }
  driver.init(); 
  // Must come *AFTER* driver.init to override RX pin assignment
  // LED connected to PB1 (pin 6)
  pinMode(STATUSLED,OUTPUT);

  // Initialize the counter and any other data in the packet
  data.counter=0;

  // Name the sensor
  data.id = 1;
}

void loop()
{
  // Update data. 
  data.counter = (data.counter + 1 ) % 256;
  data.sense1 = analogRead(1);
  data.sense2 = analogRead(2);
  data.sense3 = analogRead(3);
  // Copy data packet into the buffer
  memcpy(buf, &data,sizeof(data));
  byte buflen=sizeof(data);
  // Send buffer
  digitalWrite(STATUSLED,HIGH);
  driver.send((uint8_t *)buf,buflen);
  driver.waitPacketSent();
  digitalWrite(STATUSLED,LOW);
  delay(LOOPDELAY);
}

