#ifndef PANEL_H
#define PANLE_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <matrix/matrix.h>

class Panel
{
public:
    Panel(int data_pin, size_t x = 0, size_t y = 0);

    void set_color(size_t, size_t, uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t white = 255);
    void set_color_HSV(size_t, size_t, uint16_t hue = 0, uint8_t saturation = 0, uint8_t value = 0);

    size_t get_x_length() const;
    size_t get_y_length() const;
    const Matrix *get_matrix();

    void begin();
    void render();
    void clear();

private:
    Matrix matrix;
    Adafruit_NeoPixel led_matrix;
    size_t x_length;
    size_t y_length;
    uint16_t pin;
};

#endif