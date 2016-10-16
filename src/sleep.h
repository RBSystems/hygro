#ifndef SLEEP_h
#define SLEEP_h

#include "task.h"

struct SleepState {
  // replace the contents with what you need
  // avoid the String class and use char[#] instead
  uint16_t someValue;
  uint8_t anotherValue;
};

class SleepClass {
  uint8_t DoSleep()
  {

    // somewhere in code, enter sleep for 60 seconds or external interrupt
    SleepState state;
    state.someValue = 3333;
    state.anotherValue = 42;
    taskManager.EnterSleep(60 * 1000000, &state, sizeof(state)); // 60 seconds
    return 0;
  }
};



#endif /* end of include guard: SLEEP_h */
