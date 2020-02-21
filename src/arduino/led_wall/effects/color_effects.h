#include "../matrix_api/matrix_api.h"

class Color_Effects
{
public:
    Color_Effects(Matrix_api, uint8_t);
    void fill(unsigned int, unsigned int, unsigned int, unsigned int white = 255);
    void strobe(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

private:
    Matrix_api led_pane;
    uint8_t interrupt_pin; //pin, which will be listened to, to interrupt the effects
    bool interrupt_effect();
};
