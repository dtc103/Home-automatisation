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

Matrix mat_mult(Matrix& other){
    //check if matrix multiplikation is even possible
    if(other.get_y_length() != this->get_x_length()){
        //TODO DO SOME ERROR HANDLING HERE
    }
    Matrix new_matrix(this->get_y_length(), other.get_y_length());

    for(size_t y = 0; y < new_matrix.get_y_length(); ++y){
        for(size_t x = 0; y < new_matrix.get_x_length(); ++x){
            size_t sum = 0;
            for(size_t i = 0; i < new_matrix.get_x_length(); ++i){
                sum += this->get_value(i, y) * other.get_value(x, i);
            }
            new_matrix.set_value(sum, x, y);
        }
    }
    return new_matrix;
}

Matrix operator+(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }
    Matrix new_matrix(this->get_x_length(), this->get_y_length())

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix(x, y) = this->get_value(x, y) + other.get_value(x, y);
        }
    }

    return new_matrix;
}

Matrix operator-(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }
    Matrix new_matrix(this->get_x_length(), this->get_y_length())

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix(x, y) = this->get_value(x, y) - other.get_value(x, y);
        }
    }

    return new_matrix;
}

Matrix operator*(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }
    Matrix new_matrix(this->get_x_length(), this->get_y_length())

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix(x, y) = this->get_value(x, y) * other.get_value(x, y);
        }
    }

    return new_matrix;
}