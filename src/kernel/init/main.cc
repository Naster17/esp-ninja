#include <Arduino.h>
#include <drivers/screen.h>
#include <drivers/serial.h>
#include <drivers/touch.h>
#include <kernel/packages.h>
#include <lib/ui.h>

/*
 * If you are surprised by this code and are not very familiar with the C
 * language and its philosophy, cus this is an intermediate layer between
 * simplicity and community support, and low-level code on C All the
 * complications in the form of my wrappers around the functions of libraries
 * and the Arduino framework are not accidental, but created specifically for
 * the future migration to the C language. By big fat ass C++
 */

void boot();

int prt(void *p)
{
    serial_print("Test");
    return 0;
}

void setup()
{
    serial_begin(115200);
    screen_rotate(0);
    touch_rotate(0);
    boot();

    screen_printfc(0, 20, "wewe %s dick %d\n", "cock", 32);

    bar_navigation();
    bar_status();

    pkg_add("Wewe", "boy", prt);
    pkg_add("Wewe2", "boy2", prt);
    pkg_add("Wewe3", "boy3", prt);
    pkg_debug();
}

void loop()
{
    unsigned long startTime = millis();
    touch_state_t state = touch_get_state();

    unsigned long endTime = millis();
    unsigned long executionTime = endTime - startTime;

    if (state.state == TOUCH_DOUBLE_CLICK)
    {
        serial_print("DOUBLE CLICK!\n");
        delay(150); // pseudo work dalay
    }
    else if (state.state == TOUCH_LONG_PRESS)
    {
        serial_print("LONG PRESS!\n");
        delay(200); // pseudo work dalay
    }
    else if (state.state == TOUCH_CLICK)
    {
        serial_print("CLICK!\n");
    }
    else if (state.state == TOUCH_SWIPE_DOWN)
    {
        serial_print("SWIPE DOWN!\n");
        delay(100); // pseudo work dalay
    }
    else if (state.state == TOUCH_SWIPE_UP)
    {
        serial_print("SWIPE UP!\n");
        delay(100); // pseudo work dalay
    }
    else if (state.state == TOUCH_SWIPE_LEFT)
    {
        serial_print("SWIPE LEFT!\n");
        delay(100); // pseudo work dalay
    }
    else if (state.state == TOUCH_SWIPE_RIGHT)
    {
        serial_print("SWIPE RIGHT!\n");
        delay(100); // pseudo work dalay
    }

    if (state.point.z >= 1)
    {
        serial_printf("time: %lu ms\n", executionTime);
        serial_printf("pos: x: %d, y: %d, z: %d\n\n", state.point.x, state.point.y, state.point.z);
        bar_navigation();
        bar_status();
    }
}
