#ifndef DRIVER_TOUCH_H
#define DRIVER_TOUCH_H

#include <Arduino.h>

int touch_init();
void touch_rotate(uint8_t r);
bool touch_touched();

#endif
