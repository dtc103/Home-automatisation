#ifndef STRIP_H
#define STRIP_H

#include <Adafruit_NeoPixel.h>

class strip{
public:
    explicit strip(unsigned int, unsigned int);
    ~strip();

    unsigned int get_led_count() const;

    void set_led(unsigned int);
    void set_led(unsigned int, unsigned int, unsigned int, unsigned int);
    void set_led(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

    void set_led_HSV(unsigned int, unsigned int, unsigned int); //with gamma correction

    void set_brightness(unsigned int);

    void render();

    void turn_off();

private:
    Adafruit_NeoPixel _strip;
    
    unsigned int _data_pin;
    unsigned int _led_count;


};

#endif