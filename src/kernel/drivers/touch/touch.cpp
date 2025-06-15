#include <Arduino.h>
#include <drivers/cyd28.h>
#include <drivers/touch.h>

CYD28_TouchR touch(TFT_HEIGHT, TFT_WIDTH);

// For feature maybe rewrite to pure C
// But create nice arch now

extern uint8_t SCREEN_ROTATE;

// touch
bool touch_init()
{
    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    if (!touch.begin())
    {
        return false;
    }
    else
    {
        return true;
        touch.setRotation(SCREEN_ROTATE);
        touch.setThreshold(50);
    }
}
