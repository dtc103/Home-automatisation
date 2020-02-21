#include <Arduino.h>

bool interrupt_effect(uint8_t interrupt_pin)
{
    //check if interrupt happened, when yes, stop effect
    //Idea: if there are queries to stop the effect from the website or tranceiver, change the pin voltage from
    //one pin to HIGH. The interrupt effect function will always check the state of this pin and if its
    //HIGH it stops teh effect, otherwise it goes one

    return (bool)digitalRead(interrupt_pin);
}