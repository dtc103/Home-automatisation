#include "matrix.h"

class LED_Matrix : Matrix<int>
{
public:
    LED_Matrix(/*the object for the led_strip*/, int x_size, int y_size);

private:
};

//i have to map the matrix to the individual leds from the led strip