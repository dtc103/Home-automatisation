#include "panel.h"

Panel::Panel(int data_pin, size_t x, size_t y)
    : x_length{x}, y_length{y}, pin{data_pin}
{
    //because I dont know why, we only can assign new obejcts
    //in the init function and not in this constructor
    matrix = Matrix(x_length, y_length);
    
    //Because the dataline starts at the lower right corner of the matrix
    //the numbers of the intern matrix will be mapped as follows
    bool change_direction = true;
    size_t counter = 0;
    size_t matrix_x_length = matrix.get_x_length();
    size_t matrix_y_length = matrix.get_y_length();

    for (size_t y = 0; y < matrix_y_length; ++y)
    {
        if (change_direction)
        {
            for (size_t x = 0; x < matrix_x_length; ++x)
            {
                matrix.set_value(counter, matrix_x_length - 1 - x, matrix_y_length - 1 - y);
                ++counter;
            }
            change_direction = !change_direction;
        }
        else
        {
            for (size_t x = 0; x < matrix_x_length; ++x)
            {
                matrix.set_value(counter, x, matrix_y_length - 1 - y);
                ++counter;
            }
            change_direction = !change_direction;
        }
    }

}

void Panel::set_color(size_t x, size_t y, uint8_t red = 0, uint8_t green = 0, uint8_t blue = 0, uint8_t white = 255)
{
    led_matrix.setPixelColor(matrix.get_value(x, y), red, green, blue, white);
}

void Panel::set_color_HSV(size_t x, size_t y, uint16_t hue = 0, uint8_t saturation = 0, uint8_t value = 0)
{
    led_matrix.setPixelColor(matrix.get_value(x, y), led_matrix.gamma32(led_matrix.ColorHSV(hue, saturation, value)));
}

size_t Panel::get_x_length() const
{
    return matrix.get_x_length();
}

size_t Panel::get_y_length() const
{
    return matrix.get_y_length();
}

const Matrix *Panel::get_matrix()
{
    return &matrix;
}

//has to be called in setup loop
void Panel::begin()
{
    led_matrix = Adafruit_NeoPixel(x_length * y_length, pin, NEO_GRB + NEO_KHZ800);
    
    led_matrix.begin();
    led_matrix.clear();
    led_matrix.show(); //intitialize all pixels to "off"
}

void Panel::render()
{
    led_matrix.show();
}

void Panel::clear()
{
    led_matrix.clear();
}
