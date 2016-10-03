#include "WiFiSetup.h"


uint8_t WiFiSetupClass::begin()
{
  WiFiSetupClass::readConfig();

  setupWiFi();
}

uint8_t WiFiSetupClass::end()
{
  WiFiSetupClass::writeConfig();
}

uint8_t WiFiSetupClass::loop()
{

}

void WiFiSetupClass::readConfig(){
  getRawConfiguration();
  if (_rawConfiguration) {
      DynamicJsonBuffer jsonBuffer;
      JsonObject& json = jsonBuffer.parseObject(_rawConfiguration);
      if (json.success()) {
        Serial.println("\nparsed json");
        // reading wifi ap configuration
        readParameter(WiFiSetupClass::PARAM_MODE, mode, json);

      } else {
        Serial.println("failed to load json config");
      }
  } else {
    Serial.println("failed to read configuration");
    return;
  }
  //end read
}

void WiFiSetupClass::writeConfig(){
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();

  json[WiFiSetupClass::PARAM_MODE]         = mode;
  //
  File configFile = SPIFFS.open(WiFiSetupClass::CONFIG_FILE_NAME, "w");
  if (!configFile) {
    Serial.println("failed to open config file for writing");
  }
  //
  json.printTo(Serial);
  json.printTo(configFile);
  configFile.close();
}

/**
 * Try to connect to WiFi in following order:
 * 1. last stored settings
 * 2. WPS
 * 3. AP/STA
 * @return errorcode
 */
uint8_t WiFiSetupClass::setupWiFi()
{
  WiFi.beginSmartConfig();
  return 0;
}

WiFiSetupClass WiFiSetup;
