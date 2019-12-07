#include "../../matrix_api/matrix_api.h"

void fill(matrix_api led_pane, unsigned int red, unsigned int green, unsigned int blue)
{
    for (size_t i = 0; i < led_pane.get_x_length(); ++i)
    {
        for (size_t j = 0; j < led_pane.get_y_length(); ++j)
        {
            led_pane.set_color(i, j, red, green, blue);
        }
    }
}

void fill(matrix_api led_pane, unsigned int red, unsigned int green, unsigned int blue, unsigned int white)
{
    for (size_t i = 0; i < led_pane.get_x_length(); ++i)
    {
        for (size_t j = 0; j < led_pane.get_y_length(); ++j)
        {
            led_pane.set_color(i, j, red, green, blue, white);
        }
    }
}
