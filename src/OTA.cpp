#include "OTA.h"
#include "defines.h"
#include "debug.h"

uint8_t OTAClass::begin()
{
  DEBUG_SERIAL.println("<BOOT> OTA Update");
 // Port defaults to 8266
 // ArduinoOTA.setPort(8266);

 // Hostname defaults to esp8266-[ChipID]
 // ArduinoOTA.setHostname("myesp8266");

 // No authentication by default
 // ArduinoOTA.setPassword((const char *)"123");

 ArduinoOTA.onStart([]() {
   DEBUG_SERIAL.println("Start");
 });
 ArduinoOTA.onEnd([]() {
   DEBUG_SERIAL.println("\nEnd");
 });
 ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
   DEBUG_SERIAL.printf("Progress: %u%%\r", (progress / (total / 100)));
 });
 ArduinoOTA.onError([](ota_error_t error) {
   DEBUG_SERIAL.printf("Error[%u]: ", error);
   if (error == OTA_AUTH_ERROR) DEBUG_SERIAL.println("Auth Failed");
   else if (error == OTA_BEGIN_ERROR) DEBUG_SERIAL.println("Begin Failed");
   else if (error == OTA_CONNECT_ERROR) DEBUG_SERIAL.println("Connect Failed");
   else if (error == OTA_RECEIVE_ERROR) DEBUG_SERIAL.println("Receive Failed");
   else if (error == OTA_END_ERROR) DEBUG_SERIAL.println("End Failed");
 });
 ArduinoOTA.begin();
 DEBUG_SERIAL.println("Ready");
 DEBUG_SERIAL.print("IP address: ");
 DEBUG_SERIAL.println(WiFi.localIP());

  return IS_OK; //enum state_t
}

OTAClass OTA;
