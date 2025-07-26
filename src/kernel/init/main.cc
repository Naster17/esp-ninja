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
    ui_init();
    boot();

    bar_navigation();
    bar_status();

    grid_t *grid = ui_grid_new(3, 3);
    bar_navigation();
    bar_status();

    _mtx_set(grid, 0, 0, 1);
    _mtx_set(grid, 0, 1, 2);
    _mtx_set(grid, 1, 0, 3);

    serial_printf("0,0: %d\n", _mtx_get(grid, 0, 0));
    serial_printf("0,1: %d\n", _mtx_get(grid, 0, 1));
    serial_printf("1,0: %d\n", _mtx_get(grid, 1, 0));
    serial_printf("1,1: %d\n", _mtx_get(grid, 1, 1));

    ui_grid_free(grid);
}

void loop() {}
