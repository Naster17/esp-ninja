#ifndef SCREEN_DRIVER_H
#define SCREEN_DRIVER_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdint.h>

extern TFT_eSPI screen;
extern int32_t SCREEN_HEIGHT; // dymanic HEIGHT
extern int32_t SCREEN_WIDTH;  // dymanic WIDTH
#undef ILI9341_DRIVER

bool screen_init();
void screen_rotate(int r);

#endif // SCREEN_DRIVER_H
