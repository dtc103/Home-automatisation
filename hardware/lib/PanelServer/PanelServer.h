#ifndef PANEL_SERVER_H
#define PANEL_SERVER_H

#include <WiFi.h>

class PanelServer{
public:
    PanelServer(unsigned int port): port(port){}

    void begin(const char* ssid, const char* pass);
    
    //connects to access point
    bool authenticate(const char* servername, int port, const char* own_device_name);

    WiFiServer server;
    unsigned int port;
};
#endif