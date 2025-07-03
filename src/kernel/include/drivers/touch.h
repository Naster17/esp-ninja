#ifndef DRIVER_TOUCH_H
#define DRIVER_TOUCH_H

#include <Arduino.h>

typedef struct touch_point
{
    int16_t x;
    int16_t y;
    int16_t z;
} touch_point;

typedef enum touch_state_t
{
    TOUCH_NONE,
    // clicks
    TOUCH_CLICK,
    TOUCH_DOUBLE_CLICK,
    // press
    TOUCH_PRESS,
    TOUCH_PRESS_LONG,
    // swipe
    TOUCH_SWIPE_UP,
    TOUCH_SWIPE_DOWN,
    TOUCH_SWIPE_LEFT,
    TOUCH_SWIPE_RIGHT
} touch_state_t;

touch_state_t touch_get_state(touch_point *p);

touch_point touch_get_point(bool scale);

int touch_init();
void touch_rotate(uint8_t r);
bool touch_touched();

#endif
