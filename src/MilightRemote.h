#include <Arduino.h>
#include <MilightTransport.h>

#ifndef _MILIGHTREMOTE_H
#define _MILIGHTREMOTE_H

enum Button_t { NONE, ON, OFF, HUE, BRIGTHNESS,  TEMPERATURE, MODE, UP, DOWN, LEFT, RIGHT };


class MilightRemote {
public:


  typedef struct  // Any packet up to 32 bytes can be sent.
  {
      Button_t button;
      bool     longPress;
      uint8_t  groupId;
      uint16_t remoteId;
      uint8_t  hue;
      uint8_t  brightness;
      uint8_t  temperature;
      uint8_t  saturation;
      uint8_t  messageCount;
      uint8_t  programNr;
  }Status_t;

  MilightRemote(MilightTransport &miLightTransport );

  void begin(uint8_t* address);
  void end();

  // Common methods
  void pair();
  void unpair();

  virtual bool updateStatus(Status_t* status);
  bool newEvent();

protected:
  MilightTransport   &miLightTransport;
  uint8_t messageNr, messageCount;
};

#endif
