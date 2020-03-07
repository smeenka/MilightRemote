#include <Arduino.h>
#include <NRF24L01Simple.h>

#ifndef _MilightTRANSPORT_H
#define _MilightTRANSPORT_H

#if     1
#define debug(input)   { Serial.print(input);    }
#define debughex(input){ Serial.print(input,HEX);}
#define debugln(input) { Serial.println(input);  }
#else
#define debug(input)   
#define debughex(input)
#define debugln(input) 
#endif


class MilightTransport {
public:


  MilightTransport(NRF24L01Simple &radio);

  // open an communication channel for given (5 byte long) address
  // len is the lenght of the data packet (including checkum and length)
  bool openChannel (uint8_t* address, uint8_t len, uint8_t channel);		

  // check if a packet is availabel in the given channel
  bool packetAvailable();

  // get packet from radio and validate for checksum. Return true if checkum is correct
  // the caller of this function should  allocate memory for the packet 
  // Note that the packet must be 2 longer dan the actual data due to the checksum
  bool getPacket(uint8_t* packet, uint8_t len);


private:
  uint8_t reverted[32];
  void reverseBits(uint8_t* input, uint8_t* output, uint8_t len);
  bool validateChecksum(uint8_t *data, uint8_t len);   
  NRF24L01Simple &radio;
};

#endif
