#include "task.h"
#include "WebServer.h"

state_t TaskClass::begin()
{
  WebServer.begin();

  return IS_OK;
}

TaskClass Task;
