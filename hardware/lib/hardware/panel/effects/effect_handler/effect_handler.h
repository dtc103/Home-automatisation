#ifndef EFFECT_HANDLER_H
#define EFFECT_HANDLER_H

#include <Arduino.h>
#include <panel_client/panel_client.h>
#include <panel/panel.h>

class Effect_Handler{
public:
    Effect_Handler();
    bool is_interrupt();
private:
    bool interrupt = false;
    String current_effect;
    Panel_Client pc;
};

#endif