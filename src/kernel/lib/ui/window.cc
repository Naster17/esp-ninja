#include <drivers/screen.h>
#include <lib/ui.h>

window_t *ui_window_new(uint8_t flags)
{
    if (flags & WINDOW_DEFAULT) {}
    if (flags & WINDOW_FULL_BARS) {}
    // default small window
    // full screen window
    // full with bars
    // ....
}

void ui_window_set_title() {}

void ui_window_set_border_width() {}
