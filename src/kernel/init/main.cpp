#include "drivers/touch.h"
#include <Arduino.h>
#include <drivers/screen.h>
#include <drivers/serial.h>
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
    touch_point p = touch_get_point(true);
    screen_printfc(50, 100, "x: %d y: %d z: %d\n", p.x, p.y, p.z);
    screen_clear();
    delay(30);
    // this mean is pressure
    if (p.z > 1)
        serial_printf("x: %d y: %d z: %d \n", p.x, p.y, p.z);
}
