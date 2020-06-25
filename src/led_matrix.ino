#include "matrix_api.h"
#include "color_effects.h"

//#define DEBUG

Matrix_api matrix(2, 12, 20);

void setup()
{
#ifdef DEBUG
    Serial.begin(9600);
    Adafruit_NeoPixel strip(12 * 20, 3, NEO_GRB + NEO_KHZ800);
#endif

    matrix.init();
}

void loop()
{
    //Color_Effects::strobe(matrix, 255, 255, 255, 255, 200);
    Color_Effects::strobe(matrix, 12, 141, 245, 255, 100);
}
