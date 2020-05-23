#ifndef MATRIX_H
#define MATRIX_H

#include <Arduino.h>

extern int g_error_flag;

class Matrix
{
public:
    Matrix(size_t x = 1, size_t y = 1);

    void resize(size_t, size_t);
    size_t get_x_length() const;
    size_t get_y_length() const;

    void fill(size_t);

    size_t &get_value(size_t, size_t) const;
    size_t *get_pointer_to_value(size_t, size_t) const;
    void set_value(size_t, size_t, size_t);

    Matrix mat_mult(Matrix&);
    Matrix operator+(Matrix&);
    Matrix operator-(Matrix&);
    Matrix operator*(Matrix&);
private:
    size_t y_length;
    size_t x_length;

    size_t *matrix;
};

#endif
