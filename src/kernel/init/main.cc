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

    widget_t *wd = ui_button_new("wewe");
    widget_t *wd2 = ui_button_new("wewe2");
    widget_t *wd3 = ui_button_new("wewe3");
    ui_grid_attach(grid, wd, 0, 0, 1, 1);
    ui_grid_attach(grid, wd2, 2, 2, 1, 1);
    // widget_t *tmp = grid->wt_head;
    // do
    // {
    //     serial_printf("%s\n", tmp->label);
    //     tmp = tmp->next;
    // } while (tmp != NULL);

    bar_navigation();
    bar_status();
    ui_run(grid);
    ui_grid_free(grid);
}

void loop() {}
