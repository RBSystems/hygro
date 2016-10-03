#include <FS.h>
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include "Arduino.h" //https://github.com/arduino/Arduino
#include <stdio.h>

//#include <GpioPwm.h>
//#include <list>

#ifndef Esp8266Configuration_h
#define Esp8266Configuration_h



class Esp8266Configuration
{
  public:
    // Wifi ap js/json parameter naming
    const String PARAM_WIFI_AP_SSID          = "wifi_ap_ssid";
    const String PARAM_WIFI_AP_PASSWORD      = "wifi_ap_password";
    const String PARAM_WIFI_AP_ENABLED       = "wifi_ap_enabled";

    // Wifi station js/json parameter naming
    const String PARAM_WIFI_STATION_SSID     = "wifi_station_ssid";
    const String PARAM_WIFI_STATION_PASSWORD = "wifi_station_password";
    const String PARAM_WIFI_STATION_ENABLED  = "wifi_station_enabled";

    // mqtt js/json parameter naming
    const String PARAM_MQTT_ENABLED          = "mqtt_enabled";
    const String PARAM_MQTT_HOST             = "mqtt_host";
    const String PARAM_MQTT_USER             = "mqtt_user";
    const String PARAM_MQTT_PASSWORD         = "mqtt_password";
    const String PARAM_MQTT_DEVICE_NAME      = "mqtt_device_name";
    const String PARAM_MQTT_PORT             = "mqtt_port";

    const String CONFIG_FILE_NAME            = "configuration.json";

  //std::list<GpioPwm> mapTest;

  // wifi ap variables
  char* wifi_ap_ssid = new char[255];
  char* wifi_ap_password = new char[255];
  bool wifi_ap_enabled = new char[255];

  // wifi station variables
  char* wifi_station_ssid = new char[255];
  char* wifi_station_password = new char[255];
  bool wifi_station_enabled = new char[255];

  // mqtt configuration variables
  bool mqtt_enabled = new char[255];
  char* mqtt_host = new char[255];
  char* mqtt_user = new char[255];
  char* mqtt_password = new char[255];
  char* mqtt_device_name = new char[255];
  int mqtt_port = 1883;

  public:
    Esp8266Configuration(String _CONFIG_FILE_NAME);

  public:
    // read configuration from spiffs
    virtual void readConfig() = 0;

    // write configuration to spiffs
    virtual void writeConfig() = 0;

    // set wifi ap ssid (changes will not be stored until write is called)
    void setWifiApSsid(char* ssid);

    // write configuration to spiffs
    void writeConfiguration(const char* &configuration);

    // write configuration to spiffs
    void writeConfiguration(String &configuration);

    void readParameter(String parameterName, char* variable, JsonObject& json);

    void readParameter(String parameterName, int variable, JsonObject& json);



    // get the wifi ap ssid
    char* getWifiApSsid();


    // get the configuration file as char*
    String getRawConfiguration();

    // check if wifi ap configuration is valid
    bool isWifiApConfigurationValid();

    // check if wifi station configuration is valid
    bool isWifiStationConfigurationValid();

    // check if mqtt configuration is valid
    bool isMqttConfigurationValid();

private:
  String _rawConfiguration;

};

#endif
