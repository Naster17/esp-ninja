#ifndef DRIVER_TOUCH_H
#define DRIVER_TOUCH_H

#include <Arduino.h>

typedef struct touch_point
{
    int16_t x;
    int16_t y;
    int16_t z;
} touch_point;

touch_point touch_get_point(bool scale);

int touch_init();
void touch_rotate(uint8_t r);
bool touch_touched();

#endif
