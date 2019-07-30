#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix
{
public:
    Matrix();
    Matrix(size_t, size_t);

    void set_size(size_t, size_t);
    size_t get_x_length() const;
    size_t get_y_length() const;

    void fill(T);

    T &get_value(size_t, size_t) const;
    T *get_pointer_to_value(size_t, size_t) const;
    void set_value(T, size_t, size_t);

    T *operator[](size_t) const;

private:
    size_t y_length;
    size_t x_length;

    T **matrix;
};

template <typename T>
Matrix<T>::Matrix() : Matrix(0, 0)
{
}

template <typename T>
Matrix<T>::Matrix(size_t x, size_t y) : x_length{x}, y_length{y}
{
    matrix = new T *[x_length];
    for (size_t i = 0; i < x_length; ++i)
    {
        matrix[i] = new T[y_length](); //the "()" intitalizes the fields with default values
    }
}

template <typename T>
void Matrix<T>::set_size(size_t x, size_t y)
{
    if (x < x_length)
    {
        for (size_t i = x_length - 1; i >= x; --i)
        {
            delete[] matrix[i];
        }
        T **tmp = new T *[x];
        for (size_t i = 0; i < x; ++i)
        {
            tmp[i] = matrix[i];
        }
        delete[] matrix;
        matrix = tmp;
        tmp = nullptr; //i dont really have to take this step because the variable will be dropped after this block anyway
    }
    if (x > x_length)
    {
        T **tmp = new T *[x];
        for (size_t i = 0; i < x; ++i)
        {
            if (i < x_length)
            {
                tmp[i] = matrix[i];
            }
            else
            {
                tmp[i] = new T[y]();
            }
        }
        delete[] matrix;
        matrix = tmp;
    }
    x_length = x;

    if (y_length != y)
    {
        for (size_t i = 0; i < x_length; ++i)
        {
            T *tmp = new T[y]();
            size_t loopvariable = (y > y_length) ? y_length : y;
            for (size_t p = 0; p < loopvariable; ++p)
            {
                tmp[p] = matrix[i][p];
            }
            delete[] matrix[i];
            matrix[i] = tmp;
            tmp = nullptr;
        }
    }
    y_length = y;
}

template <typename T>
size_t Matrix<T>::get_x_length() const
{
    return x_length;
}

template <typename T>
size_t Matrix<T>::get_y_length() const
{
    return y_length;
}

void Matrix<T>::fill(T value)
{
    for (size_t i = 0; i < x_length; ++i)
    {
        for (size_t j = 0; j < y_length; ++j)
        {
            matrix[i][j] = value;
        }
    }
}

template <typename T>
T &Matrix<T>::get_value(size_t x, size_t y) const
{
    /*
    i wont do this check because i will ensure as a programmer not to set the values < length
    if (x >= x_length || y >= y_length)
    {
        //do something to alert the gui that the index was wrong
    }
    */
    return matrix[x][y];
}

template <typename T>
T *Matrix<T>::get_pointer_to_value(size_t x, size_t y) const
{
    return &matrix[x][y];
}

template <typename T>
void Matrix<T>::set_value(T val, size_t x, size_t y)
{
    /*
    i wont do this check because i will ensure as a programmer not to set the values < length
    if (x >= x_length || y >= y_length)
    {
       //throw exception to let the gui know sometihng bad happened
    }
    */
    matrix[x][y] = val;
}

template <typename T>
T *Matrix<T>::operator[](size_t index) const
{
    return matrix[index];
}

#ifdef DEBUG_ON_PC

#include <iostream>

template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> m)
{
    os << "[";
    for (size_t i = 0; i < m.get_y_length() - 1; ++i)
    {
        os << "\t[";
        for (size_t p = 0; p < m.get_x_length() - 1; ++p)
        {
            os << m.get_value(p, i) << ", ";
        }
        os << m.get_value(m.get_x_length() - 1, i);
        os << "],\n";
    }
    os << "\t[";
    for (size_t p = 0; p < m.get_x_length() - 1; ++p)
    {
        os << m.get_value(p, m.get_y_length() - 1) << ", ";
    }
    os << m.get_value(m.get_x_length() - 1, m.get_y_length() - 1);
    os << "]";
    os << "\t]";

    return os;
}
#endif

#endif
