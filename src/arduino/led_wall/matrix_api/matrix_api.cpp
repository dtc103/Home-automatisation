#include "Matrix_api.h"

Matrix_api::Matrix_api(int data_pin, size_t x, size_t y)
    : x_length{x}, y_length{y}
{
    matrix = Matrix<unsigned int>(x_length, y_length);
    led_matrix = Adafruit_NeoPixel(x * y, data_pin, NEO_GRB + NEO_KHZ800);

    led_matrix.begin();
    led_matrix.show(); //intitialize all pixels to "off"

    //Because the dataline starts at the lower right corner of the matrix
    //the numbers of the intern matrix will be mapped as follows
    bool change_direction = true;
    size_t counter = 0;
    size_t matrix_x_length = matrix.get_x_length();
    size_t matrix_y_length = matrix.get_y_length();

    for (size_t y = matrix_y_length - 1; y >= 0; --y)
    {
        if (change_direction)
        {
            for (size_t x = matrix_x_length - 1; x >= 0; --x)
            {
                matrix[x][y] = counter;
                change_direction = !change_direction;
                ++counter;
            }
        }
        else
        {
            for (size_t x = 0; x < matrix_x_length; ++x)
            {
                matrix[x][y] = counter;
                change_direction = !change_direction;
                ++counter;
            }
        }
    }
}

void Matrix_api::set_color(size_t x, size_t y, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int white = 255)
{
    led_matrix.setPixelColor(matrix[x][y], red, green, blue, white);
}

void Matrix_api::set_color(size_t x, size_t y, Color color)
{
    led_matrix.setPixelColor(matrix[x][y], color.r, color.g, color.b, color.a);
}

size_t Matrix_api::get_x_length() const
{
    return matrix.get_x_length();
}

size_t Matrix_api::get_y_length() const
{
    return matrix.get_y_length();
}

void Matrix_api::render()
{
    led_matrix.show();
}

void Matrix_api::clear()
{
    led_matrix.clear();
}
