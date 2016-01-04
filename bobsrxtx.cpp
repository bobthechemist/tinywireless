/*
  bobsrxtx.cpp - Library to assist with transiever applications
  Written by BoB LeSuer, 2016
  This code is public domain
  
*/

#include <bobsrxtx.h>


/*
// Not working at the moment
void statusBlink(int pin, int num)
{
  int i;
  // Should I always set output here?
  // pinMode(pin, OUTPUT);
  for (i = 0; i<num;i++);
  {
    digitalWrite(pin,LOW);
    delay(STATUSDELAY);
    digitalWrite(pin,HIGH);
    delay(STATUSDELAY);
  }
  digitalWrite(pin,LOW);
}
*/

void packet_status( packet_info &pi, uint8_t counter )
{
  // Perform some packet loss checking.
  // First time through, just store counter value
  if (!pi.started)
  {
    pi.last = counter;
    pi.started = true;
  }
  else
  {
    // Check for lost packet and increment loss counter.  
    // If counter has looped, report the packet receipt percentage
    if (counter < pi.last)
    {
       // Doesn't catch everything at loop - I don't care at the moment.
       Serial.print("Packet receipt percentage: ");
       pi.percentage = 100*(1-pi.numlost/256.);
       Serial.println(pi.percentage);
       pi.numlost = 0;
    }
    else if (counter != pi.last + 1 )
    {
      pi.numlost += counter-pi.last;
      Serial.print("packet(s) lost.  Total is: ");
      Serial.println(pi.numlost);
      
    }
    
    pi.last = counter;
  }  
}

/* 
 Add encryption to the data packet sent.  
 To use, create a key: char key[] = "my secret"
 and encrypt the data which has been memcpy'd into a buffer: xor_crypt(buf,key,sizeof(data));
 Apply the same function on the receiving end to decrypt. 
 Uses the XOR cipher
*/

void xor_crypt(byte *buf, char *key, int n)
{
  int i, k;
  k = strlen(key);
  for (i=0;i<n;i++)
  {
    buf[i]=buf[i]^key[i%k];
  }
}
