#ifndef SNAKE_H
#define SNAKE_H

#include "Arduino.h"
#include "../LED_Matrix/matrix.h"

volatile int direction = 0;
volatile bool pause = false;

class Snake
{
public:
    Snake(unsigned int x = 0, unsigned int y = 0);
    Snake(LED_Matrix);

    void start();

    //call interrupts on these functions to change snake direction
    //maybe something like changing a variable that will be changed while interrupting
    void turn_up();
    void turn_down();
    void turn_left();
    void turn_right();

    int **get_snake_array();
    int *get_apple_coords();

private:
    Matrix<int> playground;

    const unsigned int starting_size = 3;
    unsigned int snake_size;
    int **snake_array;

    int *apple_coords; //array with x and y values

    bool game_over;

    void init_snake();
    void gameloop();
    void draw_playground();
};

#endif