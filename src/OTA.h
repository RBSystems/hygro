#ifndef OTA_h
#define OTA_h

#include <Arduino.h>
#include <ArduinoOTA.h>

class OTAClass {
public:
  uint8_t begin();
};

extern OTAClass OTA;

#endif /* end of include guard: OTA_h */
