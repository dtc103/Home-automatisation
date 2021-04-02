#ifndef COLOR_EFFECTS_H
#define COLOR_EFFECTS_H

#include <panel/panel.h>
#include <random>
#include <vector>

struct Color_Effects_Static
{
    static void fill(Panel &led_panel, unsigned int red, unsigned int green, unsigned int blue, unsigned int white = 255);
};

struct Color_Effects_Dynamic{
    static void strobe(Panel &led_panel, unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time);
    static void rainbow_lane(Panel &led_panel, unsigned int lane_length = 1, unsigned int velocity = 100);
    static void color_lane(Panel &led_panel, unsigned int length = 1, unsigned int red = 255, unsigned int green = 255, unsigned int blue = 255, unsigned int white = 255, unsigned int vel = 100);
    static void drops(Panel &led_panel, unsigned int length = 5, unsigned int red = 0, unsigned int green = 255, unsigned int blue = 0, unsigned int density = 25, unsigned int vel = 100);
};
#endif