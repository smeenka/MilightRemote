#include <MilightTransport.h>


NRF24L01Simple radio(10,9);
MilightTransport transport(radio);

uint8_t ledPin = 2;
uint8_t data[10];
//uint8_t address[5] = { 0x52, 0x58, 0xB1,  0x47,  0xAA};  // rgbw address
uint8_t address[5] = { 0x55, 0x5A, 0xA0,  0x50,  0xAA};  // cct


void setup()
{
    Serial.begin(115200);
    Serial.println("MilightTransport test. Use cct milight remote please");
    transport.openChannel (address, 10, 6);
    Serial.println("intialized");

    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    radio.printDetails();
}

void loop()
{
    if (transport.packetAvailable() ) {
        if (transport.getPacket(data, 10)) {
            digitalWrite(ledPin, LOW);

            Serial.println("");
            Serial.print(" data: ");
            for (int i = 0 ; i < 10; i++){
                Serial.print(data[i], HEX);
                Serial.print(",");
            }
            digitalWrite(ledPin, HIGH);
        }else {
            Serial.print("C");
        }
    }
}