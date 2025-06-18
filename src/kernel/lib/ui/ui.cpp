#include <drivers/screen.h>
#include <lib/ui.h>

uint32_t NAVBAR_HEIGHT = SCREEN_HEIGHT / 14;

void navbar()
{
    screen_fill_rect(0, (SCREEN_HEIGHT - NAVBAR_HEIGHT), SCREEN_WIDTH, NAVBAR_HEIGHT, TFT_GREY2);
}

grid_t *ui_grid_new(uint32_t rows, uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->blk_width = SCREEN_WIDTH / cols;
    grid->blk_height = (SCREEN_HEIGHT / rows) - 99;
}
