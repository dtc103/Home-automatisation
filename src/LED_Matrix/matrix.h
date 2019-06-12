#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <typename T>
class Matrix
{
public:
    Matrix();
    Matrix(unsigned int, unsigned int);

    void set_size(unsigned int, unsigned int);
    unsigned int get_x_length();
    unsigned int get_y_length();

    T &get_value(unsigned int, unsigned int);
    T *get_pointer_to_value(unsigned int, unsigned int);
    void set_value(T, unsigned int, unsigned int);

    T *operator[](unsigned int index);

private:
    unsigned int y_length;
    unsigned int x_length;

    T **matrix;
};

template <typename T>
Matrix<T>::Matrix() : Matrix(0, 0)
{
}

template <typename T>
Matrix<T>::Matrix(unsigned int x, unsigned int y) : x_length{x}, y_length{y}
{
    matrix = new T *[x_length];
    for (unsigned int i = 0; i < x_length; ++i)
    {
        matrix[i] = new T[y_length](); //the "()" intitalizes the fields with default values
    }
}

template <typename T>
void Matrix<T>::set_size(unsigned int x, unsigned int y)
{
	if (x < x_length) {
		for (unsigned int i = x_length - 1; i >= x; --i)
		{
			delete[] matrix[i];
		}
		T** tmp = new T * [x];
		for (unsigned int i = 0; i < x; ++i) {
			tmp[i] = matrix[i];
		}
		delete[] matrix;
		matrix = tmp;
		tmp = nullptr; //i dont really have to take this step because the variable will be dropped after this block anyway
	}
    if (x > x_length)
    {
        T **tmp = new T *[x];
        for (unsigned int i = 0; i < x; ++i)
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
        for (unsigned int i = 0; i < x_length; ++i)
        {
            T *tmp = new T[y]();
            unsigned int loopvariable = (y > y_length) ? y_length : y;
            for (unsigned int p = 0; p < loopvariable; ++p)
            {
                tmp[p] = matrix[i][p];
            }
            delete[] matrix[i];
            matrix[i] = tmp;
        }
    }
    y_length = y;
}

template <typename T>
unsigned int Matrix<T>::get_x_length()
{
    return x_length;
}

template <typename T>
unsigned int Matrix<T>::get_y_length()
{
    return y_length;
}

template <typename T>
T &Matrix<T>::get_value(unsigned int x, unsigned int y)
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
T *Matrix<T>::get_pointer_to_value(unsigned int x, unsigned int y)
{
    return &matrix[x][y];
}

template <typename T>
void Matrix<T>::set_value(T val, unsigned int x, unsigned int y)
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
T *Matrix<T>::operator[](unsigned int index)
{
    return matrix[index];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, Matrix<T> m)
{
    os << "[";
    for (unsigned int i = 0; i < m.get_y_length() - 1; ++i)
    {
        os << "\t[";
        for (unsigned int p = 0; p < m.get_x_length() - 1; ++p)
        {
            os << m.get_value(p, i) << ", ";
        }
        os << m.get_value(m.get_x_length() - 1, i);
        os << "],\n";
    }
    os << "\t[";
    for (unsigned int p = 0; p < m.get_x_length() - 1; ++p)
    {
        os << m.get_value(p, m.get_y_length() - 1) << ", ";
    }
    os << m.get_value(m.get_x_length() - 1, m.get_y_length() - 1);
    os << "]";
    os << "\t]";

    return os;
}
#endif
