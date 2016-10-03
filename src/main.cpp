/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>

// include libraries
#include <Task.h>

// include sub files
#include "ConfigManager.h"
#include "WiFiSetup.h"
#include "leds.h"

class CfgBlob {
  public:
    const char* sta_ipa_addr = "";
};

TaskManager taskManager;

void setup()
{
  CfgBlob cfg;
  cfg.sta_ipa_addr = "18.117.33.201";
  configManager.addParameter("sta_ipa_addr", &cfg.sta_ipa_addr);
  configManager.begin(cfg);

  taskManager.StartTask(&LedWiFi); // start the blink task

  WiFiSetup.begin();

  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);


}

void loop()
{
  taskManager.Loop();

  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);

  // wait for a second
  delay(1000);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);

   // wait for a second
  delay(1000);
}
