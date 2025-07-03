#ifndef DRIVER_TOUCH_H
#define DRIVER_TOUCH_H

#include <Arduino.h>

// This def used for touch behavior record
// by reduce it you can get more faster feadback
// by increase you can get more acurate feadback
#define BEHAVIOR_REC 200 // ms (max is 255)

// This def used for touch aim treshold
// if you make allot misses you can increes this val
//    |
//  --O--
//    |
// 'O' is point where you touch, 'val' is max len from point
#define TOUCH_TRESHOLD 20 // pixels

typedef struct touch_point
{
    int16_t x;
    int16_t y;
    int16_t z;
} touch_point;

typedef enum touch_state
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
} touch_state;

typedef struct touch_state_t
{
    touch_state state;
    touch_point point;
} touch_state_t;

touch_state_t touch_get_state();

touch_point touch_get_point(bool scale);

int touch_init();
void touch_rotate(uint8_t r);
bool touch_touched();

#endif
