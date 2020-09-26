#include <MilightClient.h>


MilightClient::MilightClient(MilightTransport &transport) : miLightTransport(transport){
}

void MilightClient::begin(uint8_t* address){

}
void MilightClient::end(){

}

// Common methods
void MilightClient::pair(){

}
void MilightClient::unpair(){

}

bool MilightClient::newEvent(){
  return miLightTransport.packetAvailable(); 
}

