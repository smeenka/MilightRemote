#include <MilightCct.h>

MilightCct::MilightCct( MilightTransport  &transport):MilightRemote(transport)  {
}


bool MilightCct::begin(uint8_t channel){
	  uint8_t address[5] = REMOTE_ADDRESS;  // rgbw address
    return miLightTransport.openChannel (address, REMOTE_PACKET_LEN, channel);
}


/*
#define  LENGTH       0
#define  PROTOCOL     1
#define  ID_HIGH      2
#define  ID_LOW       3
#define  GROUP        4
#define  COMMAND      5
#define  PACkET_INDEX 6
*/

bool MilightCct::updateStatus(Status_t* status){
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
  return false;
}

bool MilightCct::parsePacket(Status_t* status){
	if ( packet[6] == messageNr) {
    // packet already received and parsed. Skip it
		status->messageCount++;
    return false; 
	} else {
    messageNr = packet[6];
  	status->messageCount = 1;
    status->remoteId = packet[2] << 8 | packet[3];

    status->longPress = packet[5] & 0x10;
    status->groupId   = packet[4]; 
		switch ( packet[5] & 0xF) {
    case  CCT_ALL_ON:        
      status->button = ON;
      break;  
    case  CCT_ALL_OFF:       
      status->groupId= 0; 
      status->button = OFF;
      break;  
    case  CCT_GROUP_1_ON:    
      status->groupId= 1; 
      status->button = ON;
      break;  
    case  CCT_GROUP_1_OFF:   
      status->groupId= 1; 
      status->button = OFF;
      break;  
    case  CCT_GROUP_2_ON:    
      status->groupId= 2; 
      status->button = ON;
      break;  
    case  CCT_GROUP_2_OFF:   
      status->groupId= 2; 
      status->button = OFF;
      break;  
    case  CCT_GROUP_3_ON:    
      status->groupId= 3; 
      status->button = ON;
      break;  
    case  CCT_GROUP_3_OFF:   
      status->groupId= 3; 
      status->button = OFF;
      break;  
    case  CCT_GROUP_4_ON:    
      status->groupId= 4; 
      status->button = ON;
      break;  
    case  CCT_GROUP_4_OFF:   
      status->groupId= 4; 
      status->button = OFF;
      break;  
    case  CCT_BRIGHNESS_UP :     
      status->brightness += 8; 
      status->button = UP;
      break;  
    case  CCT_BRIGHNESS_DOWN:    
      status->brightness -= 8; 
      status->button = DOWN;
      break;  
    case  CCT_TEMPERATURE_UP:    
      status->temperature += 8;
      status->button = RIGHT;
      break;  
    case  CCT_TEMPERATURE_DOWN:               
      status->temperature -= 8;
      status->button = LEFT;
      break;  
    default:
      status->button =  NONE;
      break;  
		}
    return true;
  }
}
