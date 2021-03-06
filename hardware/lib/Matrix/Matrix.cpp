#include "Matrix.h"

Matrix::Matrix(size_t x, size_t y) : x_length{x}, y_length{y}
{
    matrix = new size_t[x_length * y_length]();
}

void Matrix::resize(size_t new_x_len, size_t new_y_len)
{
    size_t *tmp = new size_t[new_x_len * new_y_len]();

    if (new_x_len <= this->x_length && new_y_len <= this->y_length)
    {
        for (int i = 0; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = this->matrix[(i * this->x_length) + j];
            }
        }
    }
    else if (new_x_len <= this->x_length && new_y_len > this->y_length)
    {
        for (int i = 0; i < this->y_length; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = this->matrix[(i * this->x_length) + j];
            }
        }
        for (int i = this->y_length; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = 0;
            }
        }
    }
    else if (new_x_len > this->x_length && new_y_len <= this->y_length)
    {
        for (int i = 0; i < new_y_len; ++i)
        {
            for (int j1 = 0; j1 < this->x_length; ++j1)
            {
                tmp[(i * new_x_len) + j1] = this->matrix[(i * this->x_length) + j1];
            }
            for (int j2 = this->x_length; j2 < new_x_len; ++j2)
            {
                tmp[(i * new_x_len) + j2] = 0;
            }
        }
    }
    else if (new_x_len > this->x_length && new_y_len > this->y_length)
    {
        for (int i = 0; i < this->y_length; ++i)
        {
            for (int j1 = 0; j1 < this->x_length; ++j1)
            {
                tmp[(i * new_x_len) + j1] = this->matrix[(i * this->x_length) + j1];
            }
            for (int j2 = this->x_length; j2 < new_x_len; ++j2)
            {
                tmp[(i * new_x_len) + j2] = 0;
            }
        }
        for (int i = this->y_length; i < new_y_len; ++i)
        {
            for (int j = 0; j < new_x_len; ++j)
            {
                tmp[(i * new_x_len) + j] = 0;
            }
        }
    }

    this->x_length = new_x_len;
    this->y_length = new_y_len;

    delete this->matrix;
    this->matrix = tmp;
}

size_t Matrix::get_x_length() const
{
    return this->x_length;
}

size_t Matrix::get_y_length() const
{
    return this->y_length;
}

void Matrix::fill(size_t value)
{
    for (size_t i = 0; i < x_length * y_length; ++i)
    {
        this->matrix[i] = value;
    }
}

size_t Matrix::get_value(size_t x, size_t y) const{
    return matrix[(y * this->x_length) + x];
}

size_t &Matrix::get_value_ref(size_t x, size_t y)
{
    return matrix[(y * this->x_length) + x];
}

const size_t *Matrix::get_pointer_to_value(size_t x, size_t y)
{
    return &matrix[(y * x_length) + x];
}

void Matrix::set_value(size_t val, size_t x, size_t y)
{
    matrix[(y * x_length) + x] = val;
}

Matrix Matrix::mat_mult(Matrix& other){
    //check if matrix multiplikation is even possible
    if(other.get_y_length() != this->get_x_length()){
        //TODO DO SOME ERROR HANDLING HERE
    }
    Matrix new_matrix(this->get_y_length(), other.get_y_length());

    for(size_t y = 0; y < new_matrix.get_y_length(); ++y){
        for(size_t x = 0; y < new_matrix.get_x_length(); ++x){
            size_t sum = 0;
            for(size_t i = 0; i < new_matrix.get_x_length(); ++i){
                sum += this->get_value_ref(i, y) * other.get_value_ref(x, i);
            }
            new_matrix.set_value(sum, x, y);
        }
    }
    return new_matrix;
}

Matrix Matrix::operator+(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }

    Matrix new_matrix(this->get_x_length(), this->get_y_length());

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix.get_value_ref(x, y) = this->get_value_ref(x, y) + other.get_value_ref(x, y);
        }
    }

    return new_matrix;
}

Matrix Matrix::operator-(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }
    Matrix new_matrix(this->get_x_length(), this->get_y_length());

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix.get_value_ref(x, y) = this->get_value_ref(x, y) - other.get_value_ref(x, y);
        }
    }

    return new_matrix;
}

Matrix Matrix::operator*(Matrix& other){
    if(other.get_x_length() != this->get_x_length() || other.get_y_length() != this->get_y_length()){
        //TODO DO SOME ERROR HANDLIHNG HERE
    }
    Matrix new_matrix(this->get_x_length(), this->get_y_length());

    for(size_t y = 0; y < this->get_y_length(); ++y){
        for(size_t x = 0; x < this->get_x_length(); ++x){
            new_matrix.get_value_ref(x, y) = this->get_value_ref(x, y) * other.get_value_ref(x, y);
        }
    }

    return new_matrix;
}
