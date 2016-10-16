#ifndef TASK_h
#define TASK_h

#include <Arduino.h>
#include <Task.h>
#include "defines.h"

class TaskClass {
public:
  state_t begin();
};

extern TaskManager taskManager;
extern TaskClass Task;

#endif /* end of include guard: TASK_h */
