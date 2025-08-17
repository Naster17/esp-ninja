#include <Arduino.h>
#include <drivers/cyd28.h>
#include <drivers/serial.h>
#include <drivers/touch.h>

#define _ti _touch_in_treshold
// found trashold read notation on TRASHOLD define
bool _touch_in_treshold(touch_point b[], touch_point m[])
{
    return (abs(b->x - m->x) <= TOUCH_TRESHOLD) && (abs(b->y - m->y) <= TOUCH_TRESHOLD);
}

// middle zone positioning of clicks
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

// trigered when 1 click peaks in record
// is same postion + treshold
bool _touch_is_click(touch_point *b)
{
    // found peak patterns
    uint16_t peaks = 0, peak_c = 0;
    touch_point middle = _middle(b);

    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        // if peak in same postion + treshold
        if (b[i].z >= 1 && _ti(b, &middle))
            peak_c++;
        // i == 254 if the latest peak is end peak
        if (peak_c >= 8 && (b[i].z == 0 || i == BEHAVIOR_REC - 1))
            peaks++;
        // reset the peak counter
        if (b[i].z <= 0)
            peak_c = 0;
    }
    return peaks == 1;
}

// trigered when 2 click peaks in record
// is same postion + treshold
bool _touch_is_double_click(touch_point *b)
{
    // found peak patterns
    uint16_t peaks = 0, peak_c = 0;
    touch_point middle = _middle(b);

    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        // if peak in same postion + treshold
        if (b[i].z >= 1 && _ti(b, &middle))
            peak_c++;
        // i == 254 if the latest peak is end peak
        if (peak_c >= 8 && (b[i].z == 0 || i == BEHAVIOR_REC - 1))
            peaks++;
        // reset the peak counter
        if (b[i].z <= 0)
            peak_c = 0;
    }
    return peaks >= 2;
}

// trigered when more then 90% of rec is press
// in same possition + treshold
bool _touch_is_long_press(touch_point *b)
{
    touch_point middle = _middle(b);
    int16_t pressed = 0, not_pressed = 0;
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        if (b[i].z >= 1 && _ti(b, &middle))
            pressed++;
        else
            not_pressed++;
    }
#ifdef DEBUG
    serial_printf("long.press: %d/%d\n", pressed, not_pressed);
#endif
    return (pressed > 0.9 * BEHAVIOR_REC);
}

bool _touch_is_swipe_down(touch_point *b)
{
    int16_t swiped = 0;
    for (uint8_t i = 1; i < BEHAVIOR_REC; i++)
    {
        if (b[i].y > b[i - 1].y)
            swiped++;
    }
#ifdef DEBUG
    serial_printf("descents.down: %d\n", swiped);
#endif
    return (swiped > SWIPE_MULTIPLER * BEHAVIOR_REC);
}

bool _touch_is_swipe_up(touch_point *b)
{
    int16_t swiped = 0;
    for (uint8_t i = 1; i < BEHAVIOR_REC; i++)
    {
        if (b[i].y < b[i - 1].y)
            swiped++;
    }
#ifdef DEBUG
    serial_printf("descents.up: %d\n", swiped);
#endif
    return (swiped > SWIPE_MULTIPLER * BEHAVIOR_REC);
}

bool _touch_is_swipe_right(touch_point *b)
{
    int16_t swiped = 0;
    for (uint8_t i = 1; i < BEHAVIOR_REC; i++)
    {
        if (b[i].x > b[i - 1].x)
            swiped++;
    }
#ifdef DEBUG
    serial_printf("descents.right: %d\n", swiped);
#endif
    return (swiped > SWIPE_MULTIPLER * BEHAVIOR_REC);
}

bool _touch_is_swipe_left(touch_point *b)
{
    int16_t swiped = 0;
    for (uint8_t i = 1; i < BEHAVIOR_REC; i++)
    {
        if (b[i].x < b[i - 1].x)
            swiped++;
    }
#ifdef DEBUG
    serial_printf("descents.left: %d\n", swiped);
#endif
    return (swiped > SWIPE_MULTIPLER * BEHAVIOR_REC);
}

void behav_debug(touch_point behavior[])
{
    bool found = false;
    serial_printf("\n=====================\n");
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        if (behavior[i].z >= 1)
            found = true;
    }

    if (!found)
        return;

    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        touch_point t = behavior[i];
        serial_printf("%d: [x: %d, y: %d, z: %d]\n", i, t.x, t.y, t.z);
    }
}

touch_state_t touch_get_state_simple()
{
    while (!touch_touched())
        ;
    touch_point t = touch_get_point(true);
    touch_state_t state_struct = {.state = TOUCH_CLICK, .point = {t.x, t.y, t.z}};
    return state_struct;
}

touch_state_t touch_get_state()
{
    touch_state_t state_struct = {.state = TOUCH_NONE, .point = {0, 0, 0}};
    touch_point *behavior = (touch_point *) calloc(BEHAVIOR_REC, sizeof(touch_point));
    // wait to user interaction to start recording
    while (!touch_touched())
        ;
    // record user interaction
    for (uint8_t i = 0; i < BEHAVIOR_REC; i++)
    {
        touch_point t = touch_get_point(true);
        *(behavior + i) = {t.x, t.y, t.z};
        delay(2); // 255 x 2 = 510ms
    }
    // analyze behavior
    touch_point middle = _middle(behavior);
    state_struct.point = {middle.x, middle.y, middle.z};

#ifdef DEBUG
    behav_debug(behavior);
    serial_printf("middle: x: %d, y: %d, z: %d\n", middle.x, middle.y, middle.z);
#endif
    // maybe fix this shit (idea with strcut but it is -200bytes from stack)
    if (_touch_is_double_click(behavior))
        state_struct.state = TOUCH_DOUBLE_CLICK;

    else if (_touch_is_long_press(behavior))
        state_struct.state = TOUCH_LONG_PRESS;

    else if (_touch_is_swipe_down(behavior))
        state_struct.state = TOUCH_SWIPE_DOWN;

    else if (_touch_is_swipe_up(behavior))
        state_struct.state = TOUCH_SWIPE_UP;

    else if (_touch_is_swipe_left(behavior))
        state_struct.state = TOUCH_SWIPE_LEFT;

    else if (_touch_is_swipe_right(behavior))
        state_struct.state = TOUCH_SWIPE_RIGHT;

    else if (_touch_is_click(behavior))
        state_struct.state = TOUCH_CLICK;

    free(behavior);
    return state_struct;
}
