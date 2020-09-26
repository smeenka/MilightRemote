#include <MilightCct.h>
#include <Adafruit_NeoPixel.h>

NRF24L01Simple radio(10,9);
MilightTransport transport(radio);
MilightCct cct(transport);

MilightRemote::Status_t status;


//MilightRemote& remote = cct;
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN     2

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  16

// NeoPixel brightness, 0 (min) to 255 (max)
#define BRIGHTNESS 50

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(uint8_t i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void setup()
{
    Serial.begin(115200);
    Serial.println("MilightTransport test. Use cct milight remote please");
    cct.begin(REMOTE_CHANNEL_LOW);
    radio.printDetails(); 

    strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
    strip.show();            // Turn OFF all pixels ASAP
    strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
    colorWipe(strip.Color(255,   0,   0)     , 50); // Red

  }

void loop()
{
    if (cct.newEvent() ) {
        if (cct.updateStatus(&status) ) {
            Serial.println("");
            Serial.print(" Button: ");
            Serial.print(status.button);
            Serial.print(" group: ");
            Serial.print(status.groupId);
            Serial.print(" remote Id: ");
            Serial.print(status.remoteId);
            Serial.print(" brightness: ");
            Serial.print(status.brightness);
            Serial.print(" temperature: ");
            Serial.print(status.temperature);
            Serial.print(" mode: ");
            Serial.print(status.programNr);
            Serial.print(" longpress: ");
            Serial.print(status.longPress);

            uint8_t h = status.temperature;
            colorWipe(strip.Color((h & 0xE0), (h & 28) <<2 , (h & 7) << 5), 10); // Red

            
        }else {
            //Serial.print(".");
        }
    }
}

