#ifndef MATRIX_API_H
#define MATRIX_API_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "matrix.h"

class matrix_api
{
public:
    explicit matrix_api(int data_pin, size_t x = 0, size_t y = 0);

    void set_color(size_t, size_t, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0);
    void set_color(size_t, size_t, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int white = 0);

    void render();

private:
    Matrix<unsigned int> *matrix;
    Adafruit_NeoPixel *led_matrix;
    size_t x_length;
    size_t y_length;
};

#endif