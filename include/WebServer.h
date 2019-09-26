#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <WiFi.h>

#include "Counts.h"

class WebServer
{
private:
    WiFiServer* serverPointer;
    Counts* cpm;
public:
    WebServer();
    WebServer(WiFiServer* serverPointer);
    ~WebServer();
    
    void serverLoop();
    void setServerPointer(WiFiServer* serverPointer);
    void setCpmPointer(Counts* cpmPointer);
};



#endif