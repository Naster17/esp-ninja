#ifndef SCREEN_DRIVER_H
#define SCREEN_DRIVER_H

#include <stdint.h>
#include <Arduino.h>
#include <TFT_eSPI.h>

extern TFT_eSPI screen;
extern int32_t SCREEN_HEIGHT; // dymanic HEIGHT
extern int32_t SCREEN_WIDTH;  // dymanic WIDTH

#ifdef ILI9341_2_DRIVER
#include "CYD28/CYD28.h"
extern CYD28_TouchR touch;
#else
#warning "using generic screen driver!"
#include "generic/generic.h"
#endif

bool screen_init();
bool touch_init();

// dynamic rotation
void set_rotate(int r);

#endif // SCREEN_DRIVER_H