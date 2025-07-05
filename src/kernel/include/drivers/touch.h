#ifndef DRIVER_TOUCH_H
#define DRIVER_TOUCH_H

#include <Arduino.h>

// This def used for touch behavior record
// by reduce it you can get more faster feadback
// by increase you can get more acurate feadback
#define BEHAVIOR_REC 200 // it * 2ms (max is 255)

// This def used for touch aim treshold
// if you make allot misses you can increes this val
//    |
//  --O--
//    |
// 'O' is point where you touch, 'val' is max len from point
#define TOUCH_TRESHOLD 20 // pixels

// This is percentage of found postions descents
// good is 0.11-0.15 is 11-15% founded descents
// -------> how many descents found is this swipe
#define SWIPE_MULTIPLER 0.14

// struct to trace touches
typedef struct touch_point
{
    int16_t x;
    int16_t y;
    int16_t z;
} touch_point;

// all touch states
typedef enum touch_state
{
    TOUCH_NONE,
    // clicks
    TOUCH_CLICK,
    TOUCH_DOUBLE_CLICK,
    // press
    TOUCH_LONG_PRESS,
    // swipe
    TOUCH_SWIPE_UP,
    TOUCH_SWIPE_DOWN,
    TOUCH_SWIPE_LEFT,
    TOUCH_SWIPE_RIGHT
} touch_state;

// touch state abstract struct type
typedef struct touch_state_t
{
    touch_state state;
    touch_point point;
} touch_state_t;

//
// Base
//

// initialize touch
int touch_init();

// rotate touch same vals for screen_rotate()
void touch_rotate(uint8_t r);

// if touch touched
bool touch_touched();

// get touch position
touch_point touch_get_point(bool scale);

//
// High Abstraction Layer
//

// get touch/swipe/press type & position
touch_state_t touch_get_state();

#endif
