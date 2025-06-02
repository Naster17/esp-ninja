#include "../led_hal.h"

#ifdef LED_GENERIC
bool generic_init()
{
    pinMode(LED_PIN, OUTPUT); // BLUE
}

#endif
