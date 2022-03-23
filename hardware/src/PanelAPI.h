#ifndef PANEL_API_H
#define PANEL_API_H

#include <Panel.h>
#include <PanelServer.h>

class PanelAPI{
    class Effects{

    };
    
    void begin();

    Panel panel;
    PanelServer server;
    bool running;
};


#endif