#include <drivers/screen.h>
#include <lib/ui.h>

ui_struct ui_st;

bool ui_init()
{
    // bigger font + half from it
    screen_set_text_size(2);
    ui_st.statbar_height = RTE(screen_get_font_height() + (screen_get_font_height() / 3));

    // default text height + 4 (2 + 2 borders)
    screen_set_text_size(1);
    ui_st.navbar_height = RTE(screen_get_font_height() + 4);

    return true;
}

int rnd_to_even(int n)
{
    if (n % 2 == 0)
        return n;
    return n + (n > 0 ? 1 : -1);
}

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

grid_t *ui_grid_new(const uint32_t rows, const uint32_t cols)
{
    // allocate cell size h/w
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    grid->cell_width = SCREEN_WIDTH / cols;
    grid->cell_height = SCREEN_HEIGHT / rows;

    // allocate grid matrix
    size_t mtx_s = (rows * cols) * sizeof(uint16_t);
    uint16_t *mtx = (uint16_t *) malloc(mtx_s);
    memset(mtx, 0, mtx_s);
    grid->mtx = mtx;

    return grid;
}

void ui_grid_free(grid_t *grid)
{
    free(grid->mtx);
    free(grid);
}
