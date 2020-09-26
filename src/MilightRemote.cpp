#include <MilightRemote.h>


MilightRemote::MilightRemote(MilightTransport &transport) : miLightTransport(transport){
}

void MilightRemote::begin(uint8_t* address){

}
void MilightRemote::end(){

}

// Common methods
void MilightRemote::pair(){

}
void MilightRemote::unpair(){

}

bool MilightRemote::newEvent(){
  return miLightTransport.packetAvailable(); 
}

