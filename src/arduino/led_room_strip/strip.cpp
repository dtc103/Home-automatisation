#include "strip.h"

strip::strip(unsigned int data_pin, unsigned int led_count) : _data_pin{data_pin}, _led_count(led_count){
    _strip = Adafruit_NeoPixel(_led_count, _data_pin, NEO_GRB + NEO_KHZ800);
    _strip.begin();
    _strip.show();
}

strip::~strip(){
    strip.clear();
}

void strip::set_led(unsigned int n, unsigned int r, unsigned int g, unsigned int b){
    _strip.setPixelColor(n, r, g, b);
}

void strip::set_led(unsigned int n, unsigned int r, unsigned int g, unsigned int b, unsigned int white){
    _strip.setPixelColor(n, r, g, b, white);
}

void strip::set_brightness(unsigned int bright){
    _strip.setBrightness(bright);
}

void strip::set_led_HSV(unsigned int n, unsigned int hue, unsigned int sat, unsigned int val){
    _strip.setPixelColor(n, _strip.gamma32(_strip.ColorHSV(hue, sat, val)));
}

void strip::render(){
    _strip.show();
}

void strip::turn_off(){
    _strip.clear();
}
