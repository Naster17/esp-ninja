#include "../led_hal.h"

// #ifdef LED_RGB
bool rgb_init()
{
    pinMode(LED_RED, OUTPUT);   // RED
    pinMode(LED_GREEN, OUTPUT); // GREEN
    pinMode(LED_BLUE, OUTPUT);  // BLUE

    // disable led
    digitalWrite(LED_RED, 1);
    digitalWrite(LED_GREEN, 1);
    digitalWrite(LED_BLUE, 1);

    return true;
}

void blink(int c, bool r, bool g, bool b)
{
    // inverting led logic LOW = HIGH
    for (int i = 0; i < c; ++i)
    {
        digitalWrite(LED_RED, r ? 0 : 1);
        digitalWrite(LED_GREEN, g ? 0 : 1);
        digitalWrite(LED_BLUE, b ? 0 : 1);
        delay(100);
        digitalWrite(LED_RED, 1);
        digitalWrite(LED_GREEN, 1);
        digitalWrite(LED_BLUE, 1);
    }
}

void set_state(bool r, bool g, bool b)
{
    digitalWrite(LED_RED, r ? 0 : 1);
    digitalWrite(LED_GREEN, g ? 0 : 1);
    digitalWrite(LED_BLUE, b ? 0 : 1);
}
// #endif