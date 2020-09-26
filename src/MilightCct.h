#include <Arduino.h>
#include <MilightClient.h>
#include <MilightTransport.h>

#ifndef _MILIGHTCCT_H
#define _MILIGHTCCT_H

#define  REMOTE_PACKET_LEN   10

// address is 0x55 0xAA 0x05 0x0A with prefix 0xAA and postfix 0x5
// This all 4 bits shifted left
#define  REMOTE_ADDRESS   { 0x55, 0x5A, 0xA0,  0x50,  0xAA}


#define  CCT_ALL_ON       		0x5
#define  CCT_ALL_OFF      		0x9
#define  CCT_GROUP_1_ON   		0x8
#define  CCT_GROUP_1_OFF  		0xB
#define  CCT_GROUP_2_ON   		0xD
#define  CCT_GROUP_2_OFF  		0x3
#define  CCT_GROUP_3_ON   		0x7
#define  CCT_GROUP_3_OFF  		0xA
#define  CCT_GROUP_4_ON   		0x2
#define  CCT_GROUP_4_OFF  		0x6
#define  CCT_BRIGHNESS_UP 		0xC
#define  CCT_BRIGHNESS_DOWN 	0x4
#define  CCT_TEMPERATURE_UP  	0xE
#define  CCT_TEMPERATURE_DOWN   0xF

#define  REMOTE_CHANNEL_LOW     (uint8_t*) 6
#define  REMOTE_CHANNEL_MEDIUM  (uint8_t*) 41  
#define  REMOTE_CHANNEL_HIGH    (uint8_t*) 76


class MilightCct : public MilightClient{
public:
  // Used to indicate that the start value for a transition should be fetched from current state

  MilightCct( MilightTransport &transport);
  bool begin(uint8_t channel);

  bool updateStatus(Status_t* status) override;
 

protected:
  uint8_t packet[REMOTE_PACKET_LEN];

  bool parsePacket(Status_t* status);
	
};

#endif
