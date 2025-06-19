#include "TFT_eSPI.h"
#include <cstdint>
#include <drivers/screen.h>
#include <kernel/mm.h>
#include <lib/ui.h>

uint32_t NAVBAR_HEIGHT;
uint32_t STATUSBAR_HEIGHT;

void navbar()
{
    screen_set_text_size(1);
    NAVBAR_HEIGHT = (screen_get_font_height() * 2) + (screen_get_font_height() / 2);

    int32_t navbar_start = SCREEN_HEIGHT - NAVBAR_HEIGHT;

    // draw main gray rect
    screen_fill_rect(0, navbar_start, SCREEN_WIDTH, NAVBAR_HEIGHT, TFT_GREY2);
    screen_draw_line(0, navbar_start, SCREEN_WIDTH, navbar_start, TFT_GREY1);

    // draw delimeter lines
    uint8_t bord_size = 2;
    int32_t bls = SCREEN_WIDTH / 3;
    screen_fill_rect(bls, navbar_start, bord_size, NAVBAR_HEIGHT, TFT_DARKGREY1);
    screen_fill_rect((bls * 2) - bord_size, navbar_start, bord_size, NAVBAR_HEIGHT, TFT_DARKGREY1);

    // draw icons
    uint8_t triag_border = 2;
    uint8_t circle_border = 2;
    screen_fill_triangle((bls * 2) + (bls / 3) + triag_border, navbar_start + triag_border,
                         (bls * 2) + (bls / 3) + triag_border, SCREEN_HEIGHT - triag_border,
                         (bls * 2) + (bls / 3) + (bls / 3) + triag_border,
                         SCREEN_HEIGHT - (NAVBAR_HEIGHT / 2), TFT_GREY3);
    screen_fill_circle(bls + (bls / 2), navbar_start + (NAVBAR_HEIGHT / 2),
                       (NAVBAR_HEIGHT / 2) - circle_border, TFT_GREY3);

    // draw strings
    screen_printfc(3, SCREEN_HEIGHT - (screen_get_font_height() * 2) - 1, "Free   %dkb",
                   mem_free_get_kb());
    screen_printfc(3, SCREEN_HEIGHT - screen_get_font_height() - 1, "Kernel %d.%d.%d", KERNEL_MAJOR,
                   KERNEL_MINOR, KERNEL_PATCH);
}

void statusbar()
{
    screen_set_text_size(1);
    STATUSBAR_HEIGHT = screen_get_font_height() + 2;

    screen_fill_rect(0, 0, SCREEN_WIDTH, STATUSBAR_HEIGHT, TFT_GREY2);

    const char *rtc = "14:20";
    screen_printfc(SCREEN_WIDTH - screen_get_text_width(rtc) - 1, 2, "%s\n", rtc);
}

grid_t *ui_grid_new(uint32_t rows, uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->blk_width = SCREEN_WIDTH / cols;
    grid->blk_height = (SCREEN_HEIGHT / rows) - 99;
}
