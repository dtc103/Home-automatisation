#include "color_effects.h"
#include "interrupt_effects.h"

void Color_Effects::fill(Matrix_api &led_pane, unsigned int red, unsigned int green, unsigned int blue, unsigned int white)
{
    for (size_t i = 0; i < led_pane.get_y_length(); ++i)
    {
        for (size_t j = 0; j < led_pane.get_x_length(); ++j)
        {
            led_pane.set_color(j, i, red, green, blue, white);
        }
    }
    led_pane.render();
}

void Color_Effects::strobe(Matrix_api &led_pane, unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time)
{
    int start_time = millis();
    bool lights_on = false;
    long rand = random(0, max_strobe_time);
    led_pane.clear();
    led_pane.render();

    while (!interrupt_effect())
    {
        if (millis() - start_time > rand)
        {
            rand = random(0, max_strobe_time);
            start_time = millis();
            if (lights_on)
            {
                led_pane.clear();
                led_pane.render();
                lights_on = false;
            }
            else
            {
                fill(led_pane, red, green, blue, max_brightness);
                lights_on = true;
            }
        }
    }
}

//TODO: delay ersetzen durch millis
//TODO: für beliebig lange strecke implementieren
void Color_Effects::rainbow_lane(Matrix_api &led_pane, unsigned int lane_length = 1, unsigned int velocity = 100)
{
    const unsigned int max_hue = 65535;
    const unsigned int length = led_pane.get_x_length() * led_pane.get_y_length();
    const float interpolation_part = (1.0f / (float)(length - 1)) * max_hue;

    bool left = true;

    if (lane_length >= length)
        lane_length = length;

    while (!interrupt_effect())
    {
        for (int y = 0; y < led_pane.get_y_length(); ++y)
        {
            //calculate x and y pos of the individual lights
            unsigned int x_pos = 0;
            unsigned int y_pos = 0;
            if (left)
            {
                for (int x = 0; x < led_pane.get_x_length(); ++x)
                {
                    for (int curr = led_pane.get_x_length() - 1 - x; curr < led_pane.get_x_length() - 1 - x + lane_length; ++curr)
                    {
                        if (curr >= led_pane.get_x_length())
                        {
                            if (y - 1 < 0)
                            {
                                x_pos = led_pane.get_x_length() - (curr - led_pane.get_x_length()) - 1;
                                y_pos = led_pane.get_y_length() - 1;
                            }
                            else
                            {
                                x_pos = led_pane.get_x_length() - (curr - led_pane.get_x_length()) - 1;
                                y_pos = y - 1;
                            }
                        }
                        else
                        {
                            x_pos = curr;
                            y_pos = y;
                        }
                        led_pane.set_color_HSV(x_pos, y_pos, led_pane.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
                    }
                    led_pane.render();
                    delay(velocity);
                    led_pane.clear();
                }
                left = !left;
            }
            else
            {
                for (int x = 0; x < led_pane.get_x_length(); ++x)
                {
                    //if lane_length isnt converted to int, the solution from x-lane_length will be unsigned and therefore never smaller than 0
                    for (int curr = x; curr > x - (int)lane_length; --curr)
                    {
                        if (curr < 0)
                        {
                            if (y - 1 < 0)
                            {
                                x_pos = -curr - 1;
                                y_pos = led_pane.get_y_length() - 1;
                            }
                            else
                            {
                                x_pos = -curr - 1;
                                y_pos = y - 1;
                            }
                        }
                        else
                        {
                            x_pos = curr;
                            y_pos = y;
                        }
                        led_pane.set_color_HSV(x_pos, y_pos, led_pane.get_matrix()->get_value(x_pos, y_pos) * interpolation_part, 255, 255);
                    }
                    led_pane.render();
                    delay(velocity);
                    led_pane.clear();
                }
                left = !left;
            }
        }
    }
}

//TODO: delay ersetzen durch millis
//TODO: für beliebig lange strecke implementieren
//TODO: macht das gleiche wie rainbow lane, nur mit eigener farbe
void Color_Effects::color_lane(Matrix_api &led_pane, unsigned int red = 255, unsigned int green = 255, unsigned int blue = 255, unsigned int white = 255, unsigned int length = 1, unsigned int velocity = 100)
{
}