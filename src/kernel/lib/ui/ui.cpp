#include "kernel/mm.h"
#include <drivers/screen.h>
#include <lib/ui.h>

uint32_t NAVBAR_HEIGHT = SCREEN_HEIGHT / 14;

void navbar()
{
    screen_set_text_size(1);
    NAVBAR_HEIGHT = (screen_get_font_height() * 2) + (screen_get_font_height() / 2);

    int32_t navbar_start = SCREEN_HEIGHT - NAVBAR_HEIGHT;
    int32_t bls = SCREEN_WIDTH / 3;

    // draw main gray rect
    screen_fill_rect(0, navbar_start, SCREEN_WIDTH, NAVBAR_HEIGHT, TFT_GREY2);
    screen_draw_line(0, navbar_start, SCREEN_WIDTH, navbar_start, TFT_GREY1);

    // draw delimeter lines
    uint8_t bord_size = 2;
    screen_fill_rect(bls, navbar_start, bord_size, NAVBAR_HEIGHT, TFT_DARKGREY1);
    screen_fill_rect((bls * 2) - bord_size, navbar_start, bord_size, NAVBAR_HEIGHT, TFT_DARKGREY1);

    // draw strings
    screen_printfc(3, TFT_HEIGHT - (screen_get_font_height() * 2) - 1, "Free   %dkb",
                   mem_free_get_kb());
    screen_printfc(3, TFT_HEIGHT - screen_get_font_height() - 1, "Kernel %d.%d.%d", KERNEL_MAJOR,
                   KERNEL_MINOR, KERNEL_PATCH);
}

grid_t *ui_grid_new(uint32_t rows, uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->blk_width = SCREEN_WIDTH / cols;
    grid->blk_height = (SCREEN_HEIGHT / rows) - 99;
}
