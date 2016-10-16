/**
 * Blink
 *
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>


// include libraries
#include <Task.h> //https://github.com/Makuna/Task.git

// include sub files
#include "WiFiSetup.h"
#include "leds.h"
#include "debug.h"
#include "OTA.h"
#include "sleep.h"

TaskManager taskManager;

void setup()
{
  #ifdef DEBUG_SERIAL
  aSerial.setPrinter(DEBUG_SERIAL);
  aSerial.setFilter(Level::v);
  DEBUG_SERIAL.begin(115200);
  #endif DEBUG_SERIAL

  SleepState state;
  if (taskManager.RestartedFromSleep(static_cast<void*>(&state), sizeof(state))) {
    // wake from sleep
    // state now contains what ever you stored in it when you called EnterSleep()
    if (state.anotherValue == 0) {
      // sleep called from second location
    }
    else {
      // sleep called from first location
    }
  }
  else {
    // normal boot
  }

  taskManager.StartTask(&LedWiFi); // start the blink task

  LedWiFi.setActivity(LED_ONCE);

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
