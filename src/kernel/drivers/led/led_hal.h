#ifndef LED_HAL_H
#define LED_HAL_H

#include <stdbool.h>
#include <stdint.h>
#include <Arduino.h>

// #ifdef LED_RGB
#define led_init rgb_init
bool rgb_init();
void blink(int c, bool r, bool g, bool b);
void set_state(bool r, bool g, bool b);

// #else
// #define led_init generic_init
// bool generic_init();
// #endif

#endif
