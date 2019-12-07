#include "strip.h"

class effects{
public:
    enum class Stormtype{SANDSTORM, THUNDERSTORM, BLIZZARD};

    static bool interrupt(){
        //Get queries from webpage and decide to go on or not
        return true;
    }

    static void fill(strip _strip, unsigned int r, unsigned int g, unsigned int b){
        for(size_t i = 0; i < _strip->get_led_count(); ++i)){
            _strip->set_led(i, r, g, b);
        }
        _strip.render();
    }

    static void fill(strip _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int white){
        for(size_t i = 0; i < _strip->get_led_count(); ++i)){
            _strip->set_led(i, r, g, b, white);
        }
        _strip.render();
    }
    
    static void strobe(strip _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int velocity){
        unsigned int timediff = millis();
        unsigned int max_time = random()

        while(!interrupt()){
            timediff = millis();
        }



        
    }

    static void fade(strip _strip, unsigned int velocity, unsigned int brightness){

    }

    static void breathe(strip _strip, unsigned int r, unsigned int g, unsigned int b){

    }

    static void breathe(strip _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int max_brightness){
        if(interrupt()) return;
    }

//DND sessions
    static void flame_flicker(strip _strip, unsigned int brightness){

    }

    static void daylight(strip _strip, unsigned byte daytime){

    }

    //same as daylight but with random clouds
    static void cloudy(strip _strip, unsigned byte daytime){

    }

    static void rainy(strip _strip, unsigned byte daytime){
        
    }

    static void desert(strip _strip, unsigned byte daytime){

    }

    static void snowy(strip _strip, unsigned byte daytime){

    }

    static void storm(strip _strip, Stormtype stormtype){
        switch(stormtype){
            Stormtype::THUNDERSTORM:
                break;
            Stormtype::BLIZZARD:
                break;
            Stormtype::SANDSTORM:
                break;
        }
    }

private:
    static uint32_t daytime_to_color(unsigned byte daytime){
        
    }
}
