
#include "Esp8266Configuration.h"

Esp8266Configuration::Esp8266Configuration(String _CONFIG_FILE_NAME)
:CONFIG_FILE_NAME(_CONFIG_FILE_NAME)
{

}

void Esp8266Configuration::setWifiApSsid(char* ssid){
  wifi_ap_ssid = ssid;
}



String Esp8266Configuration::getRawConfiguration() {
  if (SPIFFS.begin()) {
    if (_rawConfiguration == NULL) {
      if (SPIFFS.exists("/configuration.json")) {
        //     //file exists, reading and loading
        Serial.println("reading config file");
        File configFile = SPIFFS.open("/configuration.json", "r");
        if (configFile) {
          _rawConfiguration = configFile.readString();
          configFile.close();
          Serial.printf("content: ");
          Serial.println(_rawConfiguration);
          return _rawConfiguration;
        } else {
          Serial.println("error opening config file");
        }
      } else {
        Serial.println("file does not exist");
        return "{}";
      }
    } else {
      return _rawConfiguration;
    }
  } else {
    Serial.println("failed to mount FS");
    return "{}";
  }
  //end read
}

// void Esp8266Configuration::write(){
//   DynamicJsonBuffer jsonBuffer;
//   JsonObject& json = jsonBuffer.createObject();
//   json[PARAM_WIFI_AP_SSID]      = wifi_ap_ssid;
//   json[PARAM_WIFI_AP_PASSWORD]  = wifi_ap_password;
//   json[PARAM_WIFI_AP_ENABLED]   = wifi_ap_enabled;
//
//   json[PARAM_WIFI_STATION_SSID]     = wifi_station_ssid;
//   json[PARAM_WIFI_STATION_PASSWORD] = wifi_station_password;
//   json[PARAM_WIFI_STATION_ENABLED]  = wifi_station_enabled;
//
//   json[PARAM_MQTT_ENABLED]      = mqtt_enabled;
//   json[PARAM_MQTT_HOST]         = mqtt_host;
//   json[PARAM_MQTT_PORT]         = mqtt_port;
//   json[PARAM_MQTT_USER]         = mqtt_user;
//   json[PARAM_MQTT_PASSWORD]     = mqtt_password;
//   json[PARAM_MQTT_DEVICE_NAME]  = mqtt_device_name;
//   //
//   File configFile = SPIFFS.open("/configuration.json", "w");
//   if (!configFile) {
//     Serial.println("failed to open config file for writing");
//   }
//   //
//   json.printTo(Serial);
//   json.printTo(configFile);
//   configFile.close();
// };

bool Esp8266Configuration::isWifiApConfigurationValid(){

  return (
    wifi_ap_password != NULL &&
    strlen(wifi_ap_password) > 7 &&
    wifi_ap_ssid != NULL &&
    strlen(wifi_ap_ssid) >2
  );
}

bool Esp8266Configuration::isWifiStationConfigurationValid(){
  return (
    wifi_station_password != NULL &&
    strlen(wifi_station_password) > 7 &&
    wifi_station_ssid != NULL &&
    strlen(wifi_station_ssid) >2
  );
}


bool Esp8266Configuration::isMqttConfigurationValid(){
  if ( mqtt_host == NULL) return false;
  if ( mqtt_device_name == NULL) return false;
  if (mqtt_port < 1000) return false;
  if (mqtt_port > 30000) return false;
  return true;
}

void Esp8266Configuration::writeConfiguration(const char* &configuration){
  if (SPIFFS.begin()) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(configuration);
    File configFile = SPIFFS.open("/configuration.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
      return;
    }
    //
    Serial.println("Writing configuration");
    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    Serial.println("Done");
    _rawConfiguration = configuration;
  }  else {
    Serial.println("failed to open spiffs for writing");
  }
}

void Esp8266Configuration::writeConfiguration(String &configuration){
  if (SPIFFS.begin()) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.parseObject(configuration);
    File configFile = SPIFFS.open("/configuration.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
      return;
    }
    //
    Serial.println("Writing configuration");
    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    Serial.println("Done");
    _rawConfiguration = configuration;
  }  else {
    Serial.println("failed to open spiffs for writing");
  }
}

// void Esp8266Configuration::read(){
//   getRawConfiguration();
//   if (_rawConfiguration) {
//       DynamicJsonBuffer jsonBuffer;
//       JsonObject& json = jsonBuffer.parseObject(_rawConfiguration);
//       if (json.success()) {
//         Serial.println("\nparsed json");
//         // reading wifi ap configuration
//         readParameter(PARAM_WIFI_AP_SSID, wifi_ap_ssid, json);
//         readParameter(PARAM_WIFI_AP_PASSWORD, wifi_ap_password, json);
//         // reading wifi station configuration
//         readParameter(PARAM_WIFI_STATION_SSID, wifi_station_ssid, json);
//         readParameter(PARAM_WIFI_STATION_PASSWORD, wifi_station_password, json);
//         // reading mqtt configuration
//         readParameter(PARAM_MQTT_ENABLED, mqtt_enabled, json);
//         readParameter(PARAM_MQTT_HOST, mqtt_host, json);
//         readParameter(PARAM_MQTT_PORT, mqtt_port, json);
//         readParameter(PARAM_MQTT_USER, mqtt_user, json);
//         readParameter(PARAM_MQTT_PASSWORD, mqtt_password, json);
//         readParameter(PARAM_MQTT_DEVICE_NAME, mqtt_device_name, json);
//       } else {
//         Serial.println("failed to load json config");
//       }
//   } else {
//     Serial.println("failed to read configuration");
//     return;
//   }
//   //end read
// }

void Esp8266Configuration::readParameter(String parameterName, char* variable, JsonObject& json){
  if (json.containsKey(parameterName)) {
    const char* value = json[parameterName];
    if (value != NULL) {
      strcpy(variable, value);
    }
  }
}

void Esp8266Configuration::readParameter(String parameterName, int variable, JsonObject& json){
  if (json.containsKey(parameterName)) {
    const char* value = json[parameterName];
    if (value != NULL) {
      variable = atoi(value);
    }
  }
}
