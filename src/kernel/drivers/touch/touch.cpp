#include <Arduino.h>
#include <cstdint>
#include <cstdlib>
#include <drivers/cyd28.h>
#include <drivers/serial.h>
#include <drivers/touch.h>
#include <lib/ui.h>
#include <stdlib.h>
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

// TODO: make for loops dinamic, not ony with 254 it.

touch_point _middle(touch_point b[])
{
    // be avare of overflow
    int32_t max_x = 0, max_y = 0, max_z = 0;
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        max_x += b[i].x;
        max_y += b[i].y;
        max_z += b[i].z;
    }

    return {(int16_t) (max_x / BEHAVIOR_REC),  // x
            (int16_t) (max_y / BEHAVIOR_REC),  // y
            (int16_t) (max_z / BEHAVIOR_REC)}; // z
}

#define _ti _touch_in_treshold
bool _touch_in_treshold(touch_point b[], touch_point m[])
{
    return (abs(b->x - m->x) <= TOUCH_TRESHOLD) && (abs(b->y - m->y) <= TOUCH_TRESHOLD);
}

bool _touch_is_double_click(touch_point *b)
{
    // found peak patterns
    uint16_t peaks = 0;
    uint16_t peak_c = 0;
    touch_point middle = _middle(b);
    serial_printf("middle: %d, %d, %d\n", middle.x, middle.y, middle.z);

    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        // if peak in same postion + treshold
        if (b[i].z >= 1 && _ti(b, &middle))
            peak_c += 1;
        // i == 254 if the latest peak is end peak
        if (peak_c >= 8 && (b[i].z == 0 || i == BEHAVIOR_REC - 1))
            peaks += 1;
        // reset the peak counter
        if (b[i].z <= 0)
            peak_c = 0;
    }
    if (peaks >= 2)
        return true;

    return false;
}

void behav_debug(touch_point behavior[])
{
    serial_printf("\n=====================\n");
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        touch_point t = behavior[i];
        serial_printf("%d: [x: %d, y: %d, z: %d]\n", i, t.x, t.y, t.z);
    }
}

touch_state_t touch_get_state(touch_point p[])
{
    touch_state_t state_struct = {.state = TOUCH_NONE, .point = {0, 0, 0}};
    touch_point *behavior = (touch_point *) calloc(BEHAVIOR_REC, sizeof(touch_point));
    // wait to user interaction to start recording
    for (;;)
    {
        if (touch_get_point(true).z >= 1)
            break;
    }
    // record user interaction
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        touch_point t = touch_get_point(true);
        *(behavior + i) = {t.x, t.y, t.z};
        delay(2); // 255 x 2 = 510ms
    }
    // debug
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        if (behavior[i].z >= 1)
        {
            behav_debug(behavior);
            break;
        }
    }
    // analyze behavior
    touch_point middle = _middle(behavior);
    state_struct.point = {middle.x, middle.y, middle.z};

    if (_touch_is_double_click(behavior))
        state_struct.state = TOUCH_DOUBLE_CLICK;

    free(behavior);
    return state_struct;
}
