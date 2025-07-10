#include <lib/ui.h>

#include <drivers/screen.h>

ui_struct ui_st;

bool ui_init()
{
    bool s = true;
    s = bar_init();
    return s;
}

void ui_window_new(uint8_t flags) {

}

void ui_window_set_title() {}

void ui_window_set_border_width() {}

grid_t *ui_grid_new(uint32_t rows, uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->blk_width = SCREEN_WIDTH / cols;
    grid->blk_height = (SCREEN_HEIGHT / rows) - 99;
}
