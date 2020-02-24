#ifndef COLOR_EFFECTS_H
#define COLOR_EFFECTS_H

#include "matrix_api.h"

struct Color_Effects
{
    static void fill(Matrix_api &led_pane, unsigned int red, unsigned int green, unsigned int blue, unsigned int white = 255);
    static void strobe(Matrix_api &led_pane, unsigned int red, unsigned int green, unsigned int blue, unsigned int max_brightness, unsigned int max_strobe_time);
    static void rainbow_lane(Matrix_api &led_pane, unsigned int length = 1, unsigned int velocity = 100);
    static void color_lane(Matrix_api &led_pane, unsigned int red = 255, unsigned int green = 255, unsigned int blue = 255, unsigned int white = 255, unsigned int length = 1, unsigned int velocity = 100);
};

#endif
