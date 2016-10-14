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
#include "WiFiSetup.h"
#include "leds.h"
#include "debug.h"

TaskManager taskManager;

void setup()
{

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
