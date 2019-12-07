#include "strip.h"

//TODO if possible change light depending on position later

class effects{
public:
    //Stormtypes depending on terrain
    enum class Stormtype{SANDSTORM, THUNDERSTORM, BLIZZARD};

    //TODO ensure that the brighntess will be called for all functions
    static bool interrupt_effects(){
        //if only the function for changing the brightness will be called, call it once
        //and go on with last function -> dont return true

        //Get queries from webpage and decide to go on or not
        return true;
    }

    /**
     * Fills the strip with the inserted color with full brightness
     * 
     * @param _strip the led strip
     * @param r rgb red value
     * @param g rgb green value
     * @param b rgb blue value
     */
    static void fill(strip& _strip, unsigned int r, unsigned int g, unsigned int b){
        for(size_t i = 0; i < _strip->get_led_count(); ++i)){
            _strip->set_led(i, r, g, b);
        }
        _strip.render();
    }

    /**
     * Fills the strip with the inserted color
     * 
     * @param _strip the led strip
     * @param r rgb red value
     * @param g rgb green value
     * @param b rgb blue value
     * @param brightness strip brigntess
     */
    static void fill(strip& _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int white){
        for(size_t i = 0; i < _strip->get_led_count(); ++i)){
            _strip->set_led(i, r, g, b, white);
        }
        _strip.render();
    }
    
    /**
     * A funciton for simulating strobelight on the led strip
     * 
     * @param _strip the led strip
     * @param r rgb red value
     * @param g rgb green value
     * @param b rgb blue value
     * @param velocity the strobe velocity between 0 and 1000
     */
    static void strobe(strip& _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int velocity, unsigned int brightness){
        r = (r > 255) ? 255 : r;
        g = (g > 255) ? 255 : g;
        b = (b > 255) ? 255 : b;
        velocity = (velocity > 1000) ? 1000 : velocity;

        const int minimal_timevalue = 20;
        unsigned int starttime = millis();
        unsigned int max_time = random(minimal_timevalue + 1000 - velocity);
        bool is_on = false;

        _strip.turn_off();

        while(!interrupt_effects()){
            if(is_on && millis() - starttime > max_time){
                fill(_strip, 0, 0, 0, brightness); //turn light off
                is_on = false;
                max_time = random(minimal_timevalue + 1000 - velocity);
                starttime = millis();
            }
            if(!is_on && millis() - starttime > max_time){
                fill(_strip, 255, 255, 255, brightness); //turn light on
                is_on = true;
                max_time = random(minimal_timevalue + 1000 - velocity);
                starttime = millis();
            }
        } 
    }

    /**
     * A function for colorfading
     * 
     * @param _strip the led strip
     * @param velocity fading velocity
     * @param brigthness the brightness of the color
     */
    static void fade(strip& _strip, unsigned int velocity, unsigned int brightness){
        velocity = (velocity > 1000) ? 1000 : velocity;
        brightness = (brightness > 255) ? 255 : brightness;

        unsigned int starttime = millis();
        unsigned int max_time = velocity;

        const unsigned int hsv_max = 360; //TODO max hsv_value might be more

        while(!interrupt_effects()){
            for(unsigned int i = 0; i < hsv_max; ++i){
                if(millis() - starttime > max_time){
                    starttime = millis();

                    for(unsigned int led = 0; led < _strip.get_led_count(); ++led){
                        _strip.set_led_HSV(brightness, MAX, i); //TODO get maximal hsv value and saturation value
                    }
                    _strip.render();
                }
            } 
        }       
    }

    /**
     * Function for simulating the bretahe effect
     * 
     * @param _strip the led strip
     * @param r rgb red value
     * @param g rgb green value
     * @param b rgb blue value
     * @param brightness the maximal brightness of breathing in 
     */
    static void breathe(strip& _strip, unsigned int r, unsigned int g, unsigned int b, unsigned int brightness){
        r = (r > 255) ? 255 : r;
        g = (g > 255) ? 255 : g;
        b = (b > 255) ? 255 : b;
        brightness = (brightness > 255) ? 255 : brightness;

        unsigned int start_brightness = brightness;

        bool breathe_in = false;

        while(!interrupt_effects()){
            if(brightness >= 255) breathe_in = false;
            if(brightness <= 0) breathe_in = true;

            fill(_strip, r, g, b, brightness);

            if(breathe_in){
                ++brightness;
            }else{
                --brightness;
            }
        }
    }

//DND sessions ////////////////////////////////////////////////////////////////////////
    static void flame_flicker(strip& _strip, unsigned int brightness){
        brightness = (brightness > 255) ? 255 : brightness;
        unsigned int flameflicker = random(75); //TODO has to be changed later maybe

        //TODO switch between orange and red
        while(!interrupt_effects()){

        }
    }

    static void daylight(strip& _strip, unsigned int daytime){

    }

    //same as daylight but with random clouds
    static void cloudy(strip& _strip, unsigned int daytime){

    }

    static void rainy(strip& _strip, unsigned int daytime){
        
    }

    static void desert(strip& _strip, unsigned int daytime){

    }

    static void snowy(strip& _strip, unsigned int daytime){

    }

    static void storm(strip& _strip, Stormtype stormtype){
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