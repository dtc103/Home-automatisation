#include "color_effects.h"


void Color_Effects::fill(Panel &led_panel, unsigned int red, unsigned int green, unsigned int blue, unsigned int white)
{
    for (size_t i = 0; i < led_panel.get_y_length(); ++i)
    {
        for (size_t j = 0; j < led_panel.get_x_length(); ++j)
        {
            led_panel.set_color(j, i, red, green, blue, white);
        }
    }
    led_panel.render();
}

//FIXME: strobe stops after a certain amount of time
void Color_Effects::strobe(Panel &led_panel, unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time)
{
    int start_time = millis();
    bool lights_on = false;
    long rand = random(0, max_strobe_time);
    led_panel.clear();
    led_panel.render();

    
    if (millis() - start_time > rand)
    {
        rand = random(0, max_strobe_time);
        start_time = millis();
        if (lights_on)
        {
            led_panel.clear();
            led_panel.render();
            lights_on = false;
        }
        else
        {
            fill(led_panel, red, green, blue, max_brightness);
            lights_on = true;
        }
    }
    
}

//TODO: delay ersetzen durch millis
void Color_Effects::rainbow_lane(Panel &led_panel, unsigned int lane_length, unsigned int velocity)
{
    const unsigned int max_hue = 65535;
    const unsigned int length = led_panel.get_x_length() * led_panel.get_y_length();
    const float interpolation_part = (1.0f / (float)(length - 1)) * max_hue;

    bool left = true;

    if (lane_length >= length)
        lane_length = length;


    for (unsigned int y = 0; y < led_panel.get_y_length(); ++y)
    {
        //calculate x and y pos of the individual lights
        unsigned int x_pos = 0;
        unsigned int y_pos = 0;
        unsigned int y_shift = 0; //y_shift calculates the distance from the curr led y-pos to the first led y_pos
        if (left)
        {
            for (unsigned int x = 0; x < led_panel.get_x_length(); ++x)
            {
                for (unsigned int curr = led_panel.get_x_length() - 1 - x; curr < led_panel.get_x_length() - 1 - x + lane_length; ++curr)
                {
                    y_shift = curr / led_panel.get_x_length();
                    //calculate y_pos
                    y_pos = (led_panel.get_y_length() + (y - y_shift)) % led_panel.get_y_length();
                    //calculate x_pos
                    if (y_shift % 2 == 0)
                    {
                        x_pos = curr % led_panel.get_x_length();
                    }
                    else
                    {
                        x_pos = (led_panel.get_x_length() - 1) - (curr % led_panel.get_x_length());
                    }
                    led_panel.set_color_HSV(x_pos, y_pos, led_panel.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
                }
                led_panel.render();
                delay(velocity);
                led_panel.clear();
            }
            left = !left;
        }
        else
        {
            for (unsigned int x = 0; x < led_panel.get_x_length(); ++x)
            {
                //if lane_length isnt converted to int, the solution from x-lane_length will be unsigned and therefore never smaller than 0
                for (unsigned int curr = 0; curr < lane_length; ++curr)
                {
                    y_shift = (led_panel.get_x_length() - 1 - x + curr) / led_panel.get_x_length();
                    y_pos = (led_panel.get_y_length() + (y - y_shift)) % led_panel.get_y_length();
                    
                    if (y_shift % 2 == 0)
                    {
                        x_pos = led_panel.get_x_length() - 1 - ((led_panel.get_x_length() - 1 - x + curr) % led_panel.get_x_length());
                    }
                    else
                    {
                        x_pos = (led_panel.get_x_length() - 1 - x + curr) % led_panel.get_x_length();
                    }
                    led_panel.set_color_HSV(x_pos, y_pos, led_panel.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
                }
                led_panel.render();
                delay(velocity);
                led_panel.clear();
            }
            left = !left;
        }
    }

}

//TODO: delay ersetzen durch millis
void Color_Effects::color_lane(Panel &led_panel, unsigned int lane_length, unsigned int red, unsigned int green, unsigned int blue, unsigned int white, unsigned int velocity)
{
    const unsigned int max_length = led_panel.get_x_length() * led_panel.get_y_length();
    bool left = true;

    if (lane_length >= max_length)
        lane_length = max_length;


    for (unsigned int y = 0; y < led_panel.get_y_length(); ++y)
    {
        //calculate x and y pos of the individual lights
        unsigned int x_pos = 0;
        unsigned int y_pos = 0;
        unsigned int y_shift = 0; //y_shift calculates the distance from the curr led y-pos to the first led y_pos
        if (left)
        {
            for (unsigned int x = 0; x < led_panel.get_x_length(); ++x)
            {
                //curr refers to the current x-value of the light
                for (unsigned int curr = led_panel.get_x_length() - 1 - x; curr < led_panel.get_x_length() - 1 - x + lane_length; ++curr)
                {
                    y_shift = curr / led_panel.get_x_length();
                    //calculate y_pos
                    y_pos = (led_panel.get_y_length() + (y - y_shift)) % led_panel.get_y_length();
                    //calculate x_pos
                    if (y_shift % 2 == 0)
                    {
                        x_pos = curr % led_panel.get_x_length();
                    }
                    else
                    {
                        x_pos = (led_panel.get_x_length() - 1) - (curr % led_panel.get_x_length());
                    }
                    led_panel.set_color(x_pos, y_pos, red, green, blue, white);
                }

                led_panel.render();
                delay(velocity);
                led_panel.clear();
            }
            left = !left;
        }
        else
        {
            for (unsigned int x = 0; x < led_panel.get_x_length(); ++x)
            {
                //if lane_length isnt converted to int, the solution from x-lane_length will be unsigned and therefore never smaller than 0
                for (unsigned int curr = 0; curr < lane_length; ++curr)
                {
                    y_shift = (led_panel.get_x_length() - 1 - x + curr) / led_panel.get_x_length();
                    y_pos = (led_panel.get_y_length() + (y - y_shift)) % led_panel.get_y_length();
                    
                    if (y_shift % 2 == 0)
                    {
                        x_pos = led_panel.get_x_length() - 1 - ((led_panel.get_x_length() - 1 - x + curr) % led_panel.get_x_length());
                    }
                    else
                    {
                        x_pos = (led_panel.get_x_length() - 1 - x + curr) % led_panel.get_x_length();
                    }
                    led_panel.set_color(x_pos, y_pos, red, green, blue, white);
                }

                led_panel.render();
                delay(velocity);
                led_panel.clear();
            }
            left = !left;
        }
    }

}

void Color_Effects::drops(Panel &led_panel, unsigned int length, unsigned int red, unsigned int green, unsigned int blue, unsigned int vel)
{
    
}