#include <Arduino.h>
#include <drivers/cyd28.h>
#include <drivers/touch.h>

// For feature maybe rewrite to pure C
// But create nice arch now

CYD28_TouchR touch(TFT_HEIGHT, TFT_WIDTH);

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
        touch.setThreshold(50);
        return true;
    }
}

void touch_rotate(uint8_t r)
{
    touch.setRotation(r);
}
