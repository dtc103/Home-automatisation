#ifndef MATRIX_API_H
#define MATRIX_API_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "matrix.h"
#include "../effects/colors/colors.h"

class Matrix_api
{
public:
    explicit Matrix_api(int data_pin, size_t x = 0, size_t y = 0);

    void set_color(size_t, size_t, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int white = 255);
    void set_color(size_t, size_t, Color);

    size_t get_x_length() const;
    size_t get_y_length() const;

    void render();
    void clear();

private:
    Matrix<unsigned int> matrix;
    Adafruit_NeoPixel led_matrix;
    size_t x_length;
    size_t y_length;
};

#endif