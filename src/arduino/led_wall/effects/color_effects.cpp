#include "color_effects.h"

void Color_Effects::fill(unsigned int red, unsigned int green, unsigned int blue, unsigned int white)
{
    for (size_t i = 0; i < this->led_pane.get_x_length(); ++i)
    {
        for (size_t j = 0; j < this->led_pane.get_y_length(); ++j)
        {
            this->led_pane.set_color(i, j, red, green, blue, white);
        }
    }
    this->led_pane.render();
}

void Color_Effects::strobe(unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time)
{
    int start_time = millis();
    bool lights_on = false;
    this->led_pane.clear();
    this->led_pane.render();
    while (!this->interrupt_effect())
    {
        if (millis() - start_time > random(5, max_strobe_time))
        {
            start_time = millis();
            if (lights_on)
            {
                this->led_pane.clear();
                this->led_pane.render();
            }
            else
            {
                this->fill(red, green, blue, max_brightness);
            }
        }
    }
}

bool Color_Effects::interrupt_effect()
{
    //check if interrupt happened, when yes, stop effect
    //Idea: if there are queries to stop the effect from the website or tranceiver, change the pin voltage from
    //one pin to HIGH. The interrupt effect function will always check the state of this pin and if its
    //HIGH it stops teh effect, otherwise it goes one

    return (bool)digitalRead(this->interrupt_pin);
}