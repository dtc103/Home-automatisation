#include "snake.h"

Snake::Snake(unsigned int x, unsigned int y) : playground{Matrix<int>(x, y)}
{
    game_over = true;
}

Snake::Snake(Matrix<int> playgroundsize) : playground{playgroundsize}
{
    game_over = true;
}

void Snake::start()
{
    init_snake();
    gameloop();
}

void Snake::init_snake()
{
    snake_size = starting_size;
    snake_array = new int *[snake_size];
    //set the snakes head to the middle of the field
    snake_array[0] = playground.get_pointer_to_value(playground.get_x_length / 2, playground.get_y_length / 2);
    for (unsigned int i = 0; i < snake_size; ++i)
    {
    }

    game_over = false;
}

void Snake::gameloop()
{
    while (!game_over)
    {
    }
}