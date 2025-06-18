#include <Arduino.h>
#include <drivers/cyd28.h>
#include <drivers/touch.h>

// For feature maybe rewrite to pure C
// But create nice arch now

#ifdef CYD28
CYD28_TouchR touch(TFT_HEIGHT, TFT_WIDTH);
#else
#warning "No touch drivers specified"
#endif

// touch
int touch_init()
{
    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    if (!touch.begin())
    {
        return 1;
    }
    touch.setThreshold(50);
    return 0;
}

void touch_rotate(uint8_t r)
{
    touch.setRotation(r);
}

bool touch_touched()
{
    return touch.touched();
}
