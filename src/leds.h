/*
@summary: defines leds Connected
and implements tasks for blink updates...etc.
*/

#include <Task.h>

typedef enum led_state {
  LED_ONCE = 2,
  LED_ON = 1,
  LED_OFF = 0
} led_state_t;

class LedClass
: public Task
{
public:
  LedClass(uint8_t pin, uint32_t timeInterval) : // pass any custom arguments you need
  Task(timeInterval),
  ledPin(pin),
  ledOn(false)  // initialize members here
  { };

public:
  /* external control from functions, that can switch on/off and blink once for a certain time

   */
  uint8_t setActivity(led_state_t state)
  {
    switch (state) {
      case LED_ONCE:
        OnUpdate(999);
        break;
        case LED_ON:
        
          break;
          case LED_OFF:

            break;
    }

  };


private:
  // put member variables here that are scoped to this object
  bool ledOn;
  const uint8_t ledPin; // const means can't change other than in constructor

  virtual bool OnStart() // optional
  {
    // put code here that will be run when the task starts
    ledOn = false;
    pinMode(ledPin, OUTPUT);
    return true;
  }

  virtual void OnStop() // optional
  {
    // put code here that will be run when the task stops
    ledOn = false;
    digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
  }

  virtual void OnUpdate(uint32_t deltaTime)
  {
    if (ledOn)
    {
      digitalWrite(ledPin, LOW);    // turn the LED off by making the voltage LOW
    }
    else
    {
      digitalWrite(ledPin, HIGH);   // turn the LED on (HIGH is the voltage level)
    }

    ledOn = !ledOn; // toggle led state
  }
};

class LedWiFiClass : public LedClass {
public:
  LedWiFiClass() : LedClass(LedPin,timeInterval) {};
  static const uint8_t LedPin = 13;
  static const uint32_t timeInterval = 999;
};


LedWiFiClass LedWiFi; // every second it will turn on/off the LED
