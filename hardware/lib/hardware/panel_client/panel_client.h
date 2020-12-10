#ifndef PANEL_CLIENT_H
#define PANEL_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>

class Panel_Client{
public:
    Panel_Client();

    void start();
    void listen();
    bool available() const;
};


#endif