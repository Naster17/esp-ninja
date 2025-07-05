#include <cstdint>
#include <drivers/screen.h>
#include <kernel/mm.h>
#include <lib/ui.h>

// yeh I know its look crazy
// but it is geometry dinamic screen positions

uint32_t bar_navigation_HEIGHT;
uint32_t bar_status_HEIGHT;

void bar_navigation()
{
    screen_set_text_size(1);
    bar_navigation_HEIGHT = (screen_get_font_height() * 2) + (screen_get_font_height() / 2);
    int32_t bar_navigation_start = SCREEN_HEIGHT - bar_navigation_HEIGHT;

    // draw main gray rect
    screen_fill_rect(0, bar_navigation_start, SCREEN_WIDTH, bar_navigation_HEIGHT, TFT_GREY2);
    screen_draw_line(0, bar_navigation_start, SCREEN_WIDTH, bar_navigation_start, TFT_GREY1);

    // draw delimeter lines
    uint8_t bord_size = 2;
    int32_t bls = SCREEN_WIDTH / 3;
    screen_fill_rect(bls, bar_navigation_start, bord_size, bar_navigation_HEIGHT, TFT_DARKGREY1);
    screen_fill_rect((bls * 2) - bord_size, bar_navigation_start, bord_size, bar_navigation_HEIGHT,
                     TFT_DARKGREY1);

    // draw icons
    uint8_t triag_border = 2;
    uint8_t circle_border = 2;
    screen_fill_triangle((bls * 2) + (bls / 3) + triag_border, bar_navigation_start + triag_border,
                         (bls * 2) + (bls / 3) + triag_border, SCREEN_HEIGHT - triag_border,
                         (bls * 2) + (bls / 3) + (bls / 3) + triag_border,
                         SCREEN_HEIGHT - (bar_navigation_HEIGHT / 2), TFT_GREY3);
    screen_fill_circle(bls + (bls / 2), bar_navigation_start + (bar_navigation_HEIGHT / 2),
                       (bar_navigation_HEIGHT / 2) - circle_border, TFT_GREY3);

    // draw strings
    screen_printfc(3, SCREEN_HEIGHT - (screen_get_font_height() * 2) - 1, "Free   %dkb",
                   mem_free_get_kb());
    screen_printfc(3, SCREEN_HEIGHT - screen_get_font_height() - 1, "Kernel %d.%d.%d", KERNEL_MAJOR,
                   KERNEL_MINOR, KERNEL_PATCH);
}

void bar_status()
{
    screen_set_text_size(1);
    bar_status_HEIGHT = screen_get_font_height() + 2;

    screen_fill_rect(0, 0, SCREEN_WIDTH, bar_status_HEIGHT, TFT_GREY2);

    const char *rtc = "14:20";
    screen_printfc(SCREEN_WIDTH - screen_get_text_width(rtc) - 1, 2, "%s\n", rtc);
}

grid_t *ui_grid_new(uint32_t rows, uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->blk_width = SCREEN_WIDTH / cols;
    grid->blk_height = (SCREEN_HEIGHT / rows) - 99;
}
