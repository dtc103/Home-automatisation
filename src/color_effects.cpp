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

//FIXME: strobe stops after a certain amount of time
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
void Color_Effects::rainbow_lane(Matrix_api &led_pane, unsigned int lane_length = 1, unsigned int velocity = 100)
{
    velocity = 100;

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
            int x_pos = 0;
            int y_pos = 0;
            int y_shift = 0; //y_shift calculates the distance from the curr led y-pos to the first led y_pos
            if (left)
            {

                for (int x = led_pane.get_x_length() - 1; x >= 0; --x)
                {
                    for (int curr = 0; curr < lane_length; ++curr)
                    {
                        y_shift = (x + curr) / led_pane.get_x_length();
                        //calculate y_pos
                        y_pos = ((y - y_shift) + led_pane.get_y_length()) % led_pane.get_y_length(); //I have to add led_pane.get_y_length to prevent the modulo to be
                        // Serial.print("x: ");
                        // Serial.println(x);
                        // Serial.print("curr: ");
                        // Serial.println(curr);
                        // Serial.print("y: ");
                        // Serial.println(y);
                        // Serial.print("y_shift: ");
                        // Serial.println(y_shift);
                        // Serial.print("y_pos: ");
                        // Serial.println(y_pos);
                        //calculate x_pos
                        if (y_shift % 2 == 0)
                        {
                            x_pos = (x + curr) % led_pane.get_x_length();
                        }
                        else
                        {
                            x_pos = (led_pane.get_x_length() - 1) - ((x + curr) % led_pane.get_x_length());
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
                    for (int curr = 0; curr < lane_length; ++curr)
                    {
                        y_shift = abs((x - curr - (led_pane.get_x_length() - 1)) / led_pane.get_x_length());
                        y_pos = ((y - y_shift) + led_pane.get_y_length()) % led_pane.get_y_length();
                        if (y_shift % 2 == 0)
                        {
                            x_pos = (x - curr) % led_pane.get_x_length();
                        }
                        else
                        {
                            x_pos = (led_pane.get_x_length() - 1) - ((x - curr) % led_pane.get_x_length());
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
void Color_Effects::color_lane(Matrix_api &led_pane, unsigned int lane_length = 1, unsigned int red = 255, unsigned int green = 255, unsigned int blue = 255, unsigned int white = 255, unsigned int velocity = 100)
{
    const unsigned int length = led_pane.get_x_length() * led_pane.get_y_length();
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
            unsigned int y_shift = 0; //y_shift calculates the distance from the curr led y-pos to the first led y_pos
            if (left)
            {

                for (int x = 0; x < led_pane.get_x_length(); ++x)
                {
                    for (int curr = led_pane.get_x_length() - 1 - x; curr < led_pane.get_x_length() - 1 - x + lane_length; ++curr)
                    {
                        y_shift = (x + curr) / led_pane.get_x_length();
                        //calculate y_pos
                        y_pos = (y - y_shift) % led_pane.get_y_length();
                        //calculate x_pos
                        if (y_shift % 2 == 0)
                        {
                            x_pos = (x + curr) % led_pane.get_x_length();
                        }
                        else
                        {
                            x_pos = (led_pane.get_x_length() - 1) - ((x + curr) % led_pane.get_x_length());
                        }
                        led_pane.set_color(x_pos, y_pos, red, green, blue, white);
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
                        y_shift = (x - curr) - (led_pane.get_x_length() - 1);
                        y_pos = (y - y_shift) % led_pane.get_y_length();
                        if (y_shift % 2 == 0)
                        {
                            x_pos = (x - curr) % led_pane.get_x_length();
                        }
                        else
                        {
                            x_pos = (led_pane.get_x_length() - 1) - (x - curr) % led_pane.get_x_length();
                        }
                        led_pane.set_color(x_pos, y_pos, red, green, blue, white);
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

void Color_Effects::drops(Matrix_api &led_pane, unsigned int length = 5, unsigned int red = 0, unsigned int green = 255, unsigned int blue = 0, unsigned int vel = 100)
{
    while (!interrupt_effect())
    {
    }
}