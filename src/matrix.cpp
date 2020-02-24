#include "matrix.h"

Matrix::Matrix(size_t x = 1, size_t y = 1) : x_length{x}, y_length{y}
{
    matrix = new size_t[x_length * y_length]();
}

void Matrix::resize(size_t new_x_len, size_t new_y_len)
{
    size_t *tmp = new size_t[new_x_len * new_y_len]();

    if (new_x_len <= x_length && new_y_len <= y_length)
    {
        for (int i = 0; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = this->matrix[(i * x_length) + j];
            }
        }
    }
    else if (new_x_len <= x_length && new_y_len > y_length)
    {
        for (int i = 0; i < y_length; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = this->matrix[(i * x_length) + j];
            }
        }
        for (int i = y_length; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = 0;
            }
        }
    }
    else if (new_x_len > x_length && new_y_len <= y_length)
    {
        for (int i = 0; i < new_y_len; ++i)
        {
            for (int j1 = 0; j1 < x_length; ++j1)
            {
                tmp[(i * new_x_len) + j1] = this->matrix[(i * x_length) + j1];
            }
            for (int j2 = x_length; j2 < new_x_len; ++j2)
            {
                tmp[(i * new_x_len) + j2] = 0;
            }
        }
    }
    else if (new_x_len > x_length && new_y_len > y_length)
    {
        for (int i = 0; i < y_length; ++i)
        {
            for (int j1 = 0; j1 < x_length; ++j1)
            {
                tmp[(i * new_x_len) + j1] = this->matrix[(i * x_length) + j1];
            }
            for (int j2 = x_length; j2 < new_x_len; ++j2)
            {
                tmp[(i * new_x_len) + j2] = 0;
            }
        }
        for (int i = y_length; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = 0;
            }
        }
    }

    x_length = new_x_len;
    y_length = new_y_len;

    delete matrix;
    matrix = tmp;
}

size_t Matrix::get_x_length() const
{
    return x_length;
}

size_t Matrix::get_y_length() const
{
    return y_length;
}

void Matrix::fill(size_t value)
{
    for (size_t i = 0; i < x_length * y_length; ++i)
    {
        matrix[i] = value;
    }
}

size_t &Matrix::get_value(size_t x, size_t y) const
{
    return matrix[(y * x_length) + x];
}

size_t *Matrix::get_pointer_to_value(size_t x, size_t y) const
{
    return &matrix[(y * x_length) + x];
}

void Matrix::set_value(size_t val, size_t x, size_t y)
{
    matrix[(y * x_length) + x] = val;
}
