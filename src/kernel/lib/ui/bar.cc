#include <cstdint>
#include <drivers/screen.h>
#include <drivers/serial.h>
#include <kernel/mm.h>
#include <lib/ui.h>
#include <lib/ui_colors.h>

// yeh I know its look crazy
// but it is geometry dinamic screen positions

extern ui_struct ui_st;

int rnd_to_even(int n)
{
    if (n % 2 == 0)
        return n;
    return n + (n > 0 ? 1 : -1);
}

void bar_status()
{
    screen_fill_rect(0, 0, SCREEN_WIDTH, ui_st.statbar_height, COLOR_GREY_1);
    // screen_printfc(0, 0, "%d\n", ui_st.statbar_height);
}

void bar_navigation()
{
    screen_set_text_size(1);
    screen_fill_rect(0, SCREEN_HEIGHT - ui_st.navbar_height, //
                     SCREEN_WIDTH, ui_st.navbar_height,      //
                     COLOR_GREY_1);

    // calculate the border size in px
    int16_t border = ((ui_st.navbar_height - screen_get_font_height()) / 2) + 1;
    int16_t sides = 3;

    // print kernel version
    screen_printfc(sides, (SCREEN_HEIGHT - ui_st.navbar_height) + border, // x, y
                   "%d.%d.%d", KERNEL_MAJOR, KERNEL_MINOR, KERNEL_PATCH);

    // print memory info
    const char *mem_free = mem_free_get_str();
    screen_printfc((SCREEN_WIDTH - screen_get_text_width(mem_free)) - sides, // x
                   (SCREEN_HEIGHT - ui_st.navbar_height) + border,           // y
                   "%s", mem_free);
}

void color_debug()
{
    screen_fill_rect(0, 0, SCREEN_WIDTH, 30, COLOR_GREY_1);
    screen_fill_rect(0, 30, SCREEN_WIDTH, 30, COLOR_GREY_2);
    screen_fill_rect(0, 60, SCREEN_WIDTH, 30, COLOR_GREY_3);
    screen_fill_rect(0, 90, SCREEN_WIDTH, 30, COLOR_GREY_4);
    screen_fill_rect(0, 120, SCREEN_WIDTH, 30, COLOR_GREY_5);
}
