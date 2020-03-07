#include <MilightTransport.h>

// default constructor

MilightTransport::MilightTransport(NRF24L01Simple &radioref): radio(radioref) {
}

// open an communicaiton channel for give (5 byte long) address	
bool MilightTransport::openChannel (uint8_t* address, uint8_t len, uint8_t channel){
  uint8_t rev_address[5];
  reverseBits(address,rev_address,5);

  if (!radio.begin(NRF24L01Simple::BITRATE1MBPS))
  {
        Serial.println("Cannot communicate with radio");
        while (1); // Wait here forever.
  }
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.powerUp(NRF24L01Simple::POWER_LOW, NRF24L01Simple::CHECKSUM_OFF);
  radio.setChannel(channel);

  radio.setRxPipe(1, rev_address, 5, false, 10);
  radio.startRx();
  return true;
}		


bool MilightTransport::packetAvailable(){
	radio.checkStatus();
  return radio.hasData();
}
bool MilightTransport::getPacket(uint8_t* packet, uint8_t len)
{
    ReceivePacket_t* pkt = radio.getData();
    radio.startRx();    

    uint8_t* data = pkt->data;

    reverseBits(data, packet, len);  // reverse bits
    return validateChecksum( packet, len);
}

// reverse the bits in the input byte
void MilightTransport::reverseBits(uint8_t* input, uint8_t* output, uint8_t len) {

    for (int8_t i = 0; i < len; i++){
        uint8_t inp = input[i];
        uint8_t result = 0;

        for (uint8_t j = 0 ; j < 7; j++){
            // bit 0 of  result is bit 0 if byte
            result |= (inp & 0x1);
            result = result << 1;
            inp  = inp  >> 1; 
        }
        // shift in bit 8
        result |= (inp & 0x1);
        output[i] = result;
    }
    
/*    for (int8_t i = 0; i < len; i++){
        Serial.print("i: " );
        Serial.print(i);
        Serial.print(" inp: " );
        Serial.print(input[i], HEX );
        Serial.print(" outp hex: " );
        Serial.print(output[i], HEX );
        Serial.print(" outp dec: " );
        Serial.println (output[i] );
    }
*/    
}
#define CRC_POLY 0x8408

bool MilightTransport::validateChecksum(uint8_t *data, uint8_t len) {
  uint16_t state = 0;
  for (uint8_t i = 0; i < len - 2; i++) {
    uint8_t byte = data[i];
    for (int j = 0; j < 8; j++) {
      if ((byte ^ state) & 0x01) {
        state = (state >> 1) ^ CRC_POLY;
      } else {
        state = state >> 1;
      }
      byte = byte >> 1;
    }
  }
  /*
  Serial.print(" calculated checksum: " );
  Serial.print(state, HEX );
  Serial.print(" actual: " );
  Serial.print(data[len -2], HEX );
  Serial.print("  " );
  Serial.println(data[len -1], HEX );
  */
  uint8_t l = state & 0xFF;
  uint8_t h = (state >> 8) & 0xFF;
  return l == data[len-2] && h == data[len-1];
}


