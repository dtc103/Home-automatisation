///This should be a interface to control the led_matrix

#include "Matrix.h"
#include "Adafruit_NeoPixel.h"

class LED_Matrix
{
public:
    LED_Matrix(/*the object for the led_strip*/, int x_size, int y_size);

private:
    Adafruit_NeoPixel matrix;
};

//i have to map the matrix to the individual leds from the led strip