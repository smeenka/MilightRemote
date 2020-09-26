#include <MilightRgbw.h>

MilightRgbw::MilightRgbw( MilightTransport &transport):MilightRemote(transport)  {
}

bool MilightRgbw::begin(uint8_t channel){
  	uint8_t address[5] = REMOTE_ADDRESS;  // rgbw address
    return miLightTransport.openChannel (address, REMOTE_PACKET_LEN, channel);
}


bool MilightRgbw::updateStatus(Status_t* status){
  if (miLightTransport.getPacket(packet, REMOTE_PACKET_LEN)) {

      if (parsePacket(status)) {
        return true;
      } else {
          return false;
      }
  }else {
      Serial.print("C");
      return false;
  }
}

/*
#define  LENGTH       0
#define  PROTOCOL     1
#define  ID_HIGH      2
#define  ID_LOW       3
#define  HUE          4
#define  BRIGHTNESS   5
#define  COMMAND      6
#define  PACkET_INDEX 7
*/

bool MilightRgbw::parsePacket(Status_t* status){
  uint8_t b = 0;
	if ( packet[7] == messageNr) {
    // packet already received and parsed. Skip it
		status->messageCount++;
    return false; 
	} else {
    messageNr = packet[7];
  	status->messageCount = 1;
    status->remoteId = packet[2] << 8 | packet[3];

    status->longPress = packet[6] & 0x10;
		switch ( packet[6] & 0xF) {
    case  RGBW_ALL_ON:        
      status->groupId= 0; 
      status->button = ON;
      break;  
    case  RGBW_ALL_OFF:       
      status->groupId= 0; 
      status->button = OFF;
      break;  
    case  RGBW_GROUP_1_ON:    
      status->groupId= 1; 
      status->button = ON;
      break;  
    case  RGBW_GROUP_1_OFF:   
      status->groupId= 1; 
      status->button = OFF;
      break;  
    case  RGBW_GROUP_2_ON:    
      status->groupId= 2; 
      status->button = ON;
      break;  
    case  RGBW_GROUP_2_OFF:   
      status->groupId= 2; 
      status->button = OFF;
      break;  
    case  RGBW_GROUP_3_ON:    
      status->groupId= 3; 
      status->button = ON;
      break;  
    case  RGBW_GROUP_3_OFF:   
      status->groupId= 3; 
      status->button = OFF;
      break;  
    case  RGBW_GROUP_4_ON:    
      status->groupId= 4; 
      status->button = ON;
      break;  
    case  RGBW_GROUP_4_OFF:   
      status->groupId= 4; 
      status->button = OFF;
      break;  
    case  RGBW_SPEED_UP :     
      status->button = UP;
      break;  
    case  RGBW_SPEED_DOWN:    
      status->button = DOWN;
      break;  
    case  RGBW_DISCO_MODE:    
      status->programNr = packet[1] & 0xF;
      status->button = MODE;
      break;  
    case  RGBW_HUE:               
      status->hue = packet[4];  
      status->button = HUE;
      break;  
    case  RGBW_BRIGHTNESS:  
      b = packet[5];
      // correct the strange scaling of brighness to a scale from 0 .. 
      if (b <= 161){
        status->brightness = 161 - b;
      }else {
        status->brightness = 256 - b + 161;
      }   
      status->button = BRIGTHNESS;
      break;  
    default:
      status->button =  NONE;
      break;  
		}
    return true;
  }
}
