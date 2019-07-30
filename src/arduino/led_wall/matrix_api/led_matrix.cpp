#include "led_matrix.h"

LED_Matrix::LED_Matrix(Adafruit_NeoPixel matrix, INPUT_LAYOUT layout, size_t x, size_t y)
    : led_matrix{matrix}, x_length{x}, y_length{y}
{
    led_matrix.begin();
    led_matrix.show(); //intitialize all pixels to "off"

    switch (layout)
    {
    case INPUT_LAYOUT::LEFT_UPPER_ZIGZAG:
    {
        unsigned int led_index = 0;
        bool change_direction = false;
        for (int y_index = 0; y_index < y_length; ++y_index)
        {
            if (change_direction)
            {
                unsigned int counter = x_length - 1;
                while (counter >= 0)
                {
                    matrix[counter][y_index] = led_index;
                    --counter;
                    ++led_index;
                }
                change_direction = !change_direction;
            }
            else
            {
                unsigned int counter = 0;
                while (counter < x_length)
                {
                    matrix[counter][y_index] = led_index;
                    ++counter;
                    ++led_index;
                }
                change_direction = !change_direction;
            }
        }
        break;
    }
    case INPUT_LAYOUT::LEFT_UPPER_NORMAL:
    {
        unsigned int led_index = 0;
        for (int y_index = 0; y_index < y_length; ++y_index)
        {
            for (int x_index = 0; x_index < x_length++ x_index)
            {
                matrix[x_index][y_index] = led_index;
            }
        }
        break;
    }
    case INPUT_LAYOUT::LEFT_LOWER_ZIGZAG:
    {
        bool change_direction = false;
        unsigned int led_index = 0;
        for (int y_index = y_length - 1; y_index >= 0; --y_index)
        {
            if (change_direction)
            {
                unsigned int counter = 0;
                while (counter < x_length)
                {
                    matrix[counter][y_index] = led_index;
                    ++led_index;
                }
                change_direction = !change_direction;
            }
            else
            {
                unsigned int counter = x_length - 1;
                while (counter >= 0)
                {
                    matrix[counter][y_index] = led_index;
                    ++led_index;
                }
                change_direction = !change_direction;
            }
        }
        break;
    }
    case INPUT_LAYOUT::LEFT_LOWER_NORMAL:
    {
        unsigned int led_index = (x * y) - 1;
        for (int y_index = 0; y_index < y_length; ++y_index)
        {
            for (int x_index = 0; x_index < x_length; ++x_index)
            {
                matrix[x_index][y_index] = led_index;
                --led_index;
            }
        }
        break;
    }
    case INPUT_LAYOUT::RIGHT_UPPER_ZIGZAG:
    {
        unsigned int led_index = 0;
        bool change_direction = true;
        for (unsigned int y_index = 0; y_index < y_length; ++y_index)
        {
            if (change_direction)
            {
                unsigned int counter = x_length - 1;
                while (counter >= 0)
                {
                    matrix[counter][y_index] = led_index;
                    --counter;
                }
                change_direction = !change_direction;
            }
            else
            {
                unsigned int counter = 0;
                while (counter < x_length)
                {
                    matrix[counter][y_index] = led_index;
                    --counter;
                }
                change_direction = !change_direction;
            }
        }
        break;
    }
    case INPUT_LAYOUT::RIGHT_UPPER_NORMAL:
    {
        //TODO
        break;
    }
    case INPUT_LAYOUT::RIGHT_LOWER_ZIGZAG:
    {
        unsigned int led_index = 0;
        bool change_direction = true;
        for (unsigned int y_index = y_length - 1; y_index >= 0; --y_index)
        {
            if (change_direction)
            {
                unsigned int counter = x_length - 1;
                while (counter >= 0)
                {
                    matrix[counter][y_index] = led_index;
                    --counter;
                }
                change_direction = !change_direction;
            }
            else
            {
                unsigned int counter = 0;
                while (counter < x_length)
                {
                    matrix[counter][y_index] = led_index;
                    ++counter;
                }
                change_direction = !change_direction;
            }
        }
        break;
    }
    case INPUT_LAYOUT::RIGHT_LOWER_NORMAL:
    {
        //TODO
        break;
    }
    }
}

void LED_Matrix::set_color(size_t x, size_t y, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0)
{
    led_matrix.setPixelColor(matrix[x][y], red, green, blue);
}

void LED_Matrix::set_color(size_t x, size_t y, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int white = 0)
{
    led_matrix.setPixelColor(matrix[x][y], red, green, blue, white);
}
