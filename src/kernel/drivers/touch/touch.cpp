#include <Arduino.h>
#include <cstdint>
#include <drivers/cyd28.h>
#include <drivers/serial.h>
#include <drivers/touch.h>
#include <lib/ui.h>
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

touch_point touch_get_point(bool scale)
{
    CYD28_TS_Point t;
    if (scale)
        // z is for pressure of touch
        t = touch.getPointScaled();
    else
        t = touch.getPointRaw();

    return (touch_point) {t.x, t.y, t.z};
}

#define _th _touch_position_treshhold

bool _touch_position_treshhold(int16_t p, int16_t th)
{
    if (p + th)
        ;
}

bool _touch_is_double_click(touch_point behavior[])
{
    // found peak patterns
    uint16_t peaks = 0;
    uint16_t peak_c = 0;
    for (uint8_t i = 0; i <= 254; i++)
    {
        touch_point t = behavior[i];
        if (t.z >= 1)
            peak_c += 1;

        if (peak_c >= 10 && t.z == 0)
            peaks += 1;

        if (t.z <= 0)
            peak_c = 0;
    }
    if (peaks >= 2)
        return true;

    return false;
}

void behav_debug(touch_point behavior[])
{
    serial_printf("\n=====================\n");
    for (uint8_t i = 0; i <= 254; i++)
    {
        touch_point t = behavior[i];
        serial_printf("%d: [x: %d, y: %d, z: %d]\n", i, t.x, t.y, t.z);
    }
}

touch_state_t touch_get_state(touch_point *p)
{
    touch_state_t state;
    touch_point behavior[255];

    for (uint8_t i = 0; i <= 254; i++)
    {
        touch_point t = touch_get_point(true);
        behavior[i] = {t.x, t.y, t.z};
        delay(2); // 255 x 4 = 1020ms
                  // 255 x 3 = 765ms
                  // 255 x 2 = 510ms
    }

    // behav_debug(behavior);
    if (_touch_is_double_click(behavior))
        return TOUCH_DOUBLE_CLICK;

    return TOUCH_NONE;
}
