#include <FS.h>
#include <ESP8266WiFi.h>

#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include <Esp8266Configuration.h>
#include <ESP8266mDNS.h>

class WiFiSetupClass : Esp8266Configuration {
public:
  uint8_t begin();
  uint8_t end();
  uint8_t loop();
  WiFiSetupClass() : Esp8266Configuration(CONFIG_FILE_NAME)  {};

  public:
    // set mqtt server port (changes will not be stored until write is called)
    int mode = 1;

  public:
    const String PARAM_MODE            = "mode";
    const String CONFIG_FILE_NAME            = "cfg/wifi.json";

  private:
    String _rawConfiguration;

    void readConfig();
    void writeConfig();

  private:
    uint8_t setupWiFi();

  protected:
    WiFiEvent_t onConnectHandler, onDisconnectHandler;
};

extern WiFiSetupClass WiFiSetup;
