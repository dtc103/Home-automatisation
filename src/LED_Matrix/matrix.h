#ifndef MATRIX_H
#define MATRIX_H

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

//TODO delete unused values
template <typename T>
void Matrix<T>::set_size(unsigned int x, unsigned int y)
{
    T **tmp_matrix = matrix;
    matrix = new T *[x];

    unsigned int i = 0;
    unsigned int p = 0;
    for (i = 0; i < x; ++i)
    {
        matrix[i] = tmp_matrix[i];
        for (p = 0; p < y; ++p)
        {
            matrix[i][p] = tmp_matrix[i][p];
        }
    }
    x_length = x;
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
    return matrix[x][y];
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

#endif
