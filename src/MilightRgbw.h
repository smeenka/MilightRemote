#include <Arduino.h>
#include <MilightClient.h>
#include <MilightTransport.h>

#ifndef _MILIGHTRGBW_H
#define _MILIGHTRGBW_H

#define  REMOTE_PACKET_LEN   10
// address is 0x25 0x8B 0x14 0x 0x7A with prefix 0xAA and postfix 0x5
// This all 4 bits shifted left
#define  REMOTE_ADDRESS    { 0x52, 0x58, 0xB1,  0x47,  0xAA}

#define  RGBW_ALL_ON       0x01
#define  RGBW_ALL_OFF      0x02
#define  RGBW_GROUP_1_ON   0x03
#define  RGBW_GROUP_1_OFF  0x04
#define  RGBW_GROUP_2_ON   0x05
#define  RGBW_GROUP_2_OFF  0x06
#define  RGBW_GROUP_3_ON   0x07
#define  RGBW_GROUP_3_OFF  0x08
#define  RGBW_GROUP_4_ON   0x09
#define  RGBW_GROUP_4_OFF  0x0A
#define  RGBW_SPEED_UP     0x0B
#define  RGBW_SPEED_DOWN   0x0C
#define  RGBW_DISCO_MODE   0x0D
#define  RGBW_BRIGHTNESS   0x0E
#define  RGBW_HUE          0x0F

#define  REMOTE_CHANNEL_LOW     11
#define  REMOTE_CHANNEL_MEDIUM  41  
#define  REMOTE_CHANNEL_HIGH    72


class MilightRgbw : public MilightClient{
public:
  // Used to indicate that the start value for a transition should be fetched from current state
  MilightRgbw( MilightTransport &transport);
  bool begin(uint8_t channel);
  bool updateStatus(Status_t* status) override;  
protected:
  uint8_t packet[REMOTE_PACKET_LEN];
  bool parsePacket(Status_t* status);

};

#endif
