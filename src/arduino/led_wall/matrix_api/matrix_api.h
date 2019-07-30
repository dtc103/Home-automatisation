#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "matrix.h"

/**
 * The origin of the matrix(matrix[0][0]) is the left upper corner.
 * The y-axis will increase by going down.
 * 
 * Explaining the following enum:
 * 
 * This enum is for mapping your matrix correctly to the cable connections
 * 
 * If you have a matrix like the following
 * 
 *      o o o o o
 *      o o o o o
 *      o o o o o
 *      o o o o o
 *      o o o o o
 * 
 * ZIGZAG means that the connections for the led strip will follow a zigzag line to the other side
 * like following: (This example is for LEFT_UPPER_ZIGZAG)
 *      
 * input->0--1--2--3--4
 *                    |
 *        9--8--7--6--5
 *        |
 *        10-11-12-13-14
 *                     |
 *        19-18-17-16-15
 *        |
 *        20-21-22-23-24
 * 
 * NORMAL means that the connections will start at the beginning like following:
 * (This example is for LEFT_UPPER_NORMAL)  (This example is for RIGHT_UPPER_NORMAL) 
 * input->0--1--2--3--4                     4--3--2--1--0 <-- input
 *        |                                             |
 *        5--6--7--8--9                     9--8--7--6--5
 *        |                                             |
 *        10-11-12-13-14                    14-13-12-11-10
 *        |                                              |
 *        15-16-17-18-19                    19-18-17-16-15
 *        |                                             |
 *        20-21-22-23-24                    24-23-22-21-20
 * 
 * Another example if you set your input from lower to upper
 * (This example is for RIGHT_LOWER_ZIGZAG):
 * 
 *        24-23-22-21-20
 *                    |
 *        15-16-17-18-19
 *        |
 *        14-13-12-11-10
 *                    |
 *        5--6--7--8--9
 *        |
 *        4--3--2--1--0 <- input
 * 
 * (This example is for RIGHT_LOWER_NORMAL):
 *        24-23-22-21-20 
 *        |
 *        19-18-17-16-15
 *        |
 *        14-13-12-11-10
 *        |
 *        9--8--7--6--5
 *        |
 *        4--3--2--1--0 <- input
 * 
 */
enum class INPUT_LAYOUT
{
    LEFT_UPPER_ZIGZAG,
    LEFT_UPPER_NORMAL,
    LEFT_LOWER_ZIGZAG,
    LEFT_LOWER_NORMAL,
    RIGHT_UPPER_ZIGZAG,
    RIGHT_UPPER_NORMAL,
    RIGHT_LOWER_ZIGZAG,
    RIGHT_LOWER_NORMAL,
};

class LED_Matrix
{
public:
    explicit LED_Matrix(Adafruit_NeoPixel, INPUT_LAYOUT, size_t x = 0, size_t y = 0);

    void set_color(size_t, size_t, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0);
    void set_color(size_t, size_t, unsigned int red = 0, unsigned int green = 0, unsigned int blue = 0, unsigned int white = 0);

    void render();

private:
    Matrix<unsigned int> led_matrix;
    Adafruit_NeoPixel led_matrix;
    size_t x_length;
    size_t y_length;
};

#endif

//i have to map the matrix to the individual leds from the led strip