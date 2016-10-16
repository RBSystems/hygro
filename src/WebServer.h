#ifndef WEBSERVER_h
#define WEBSERVER_h

#include <Arduino.h>
#include <Hash.h> //needed by ESPAsyncWebServer
#include <ESPAsyncWebServer.h>
#include <Task.h>
#include "defines.h"

class WebServerClass : public Task
{
  public:
    WebServerClass()
    :Task(1)
    ,_server(AsyncWebServer(80))
    {

    };
    
    state_t begin();

  private:
    AsyncWebServer _server;
};

extern WebServerClass WebServer;

#endif /* end of include guard: WEBSERVER_h */
