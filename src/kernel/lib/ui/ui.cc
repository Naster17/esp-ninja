#include <cstdlib>
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

uint16_t _mtx_get(grid_t *grid, size_t row, size_t col)
{
    return grid->mtx[row * grid->cols + col];
}

void _mtx_set(grid_t *grid, size_t row, size_t col, uint16_t value)
{
    grid->mtx[row * grid->cols + col] = value;
}

grid_t *ui_grid_new(const uint32_t rows, const uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    // allocate rows cols
    grid->cols = cols;
    grid->rows = rows;

    // allocate cell size h/w
    grid->cell_width = SCREEN_WIDTH / cols;
    grid->cell_height = SCREEN_HEIGHT / rows;

    // allocate grid matrix
    size_t mtx_s = (rows * cols) * sizeof(uint16_t);
    uint16_t *mtx = (uint16_t *) malloc(mtx_s);
    memset(mtx, 0, mtx_s);
    grid->mtx = mtx;

    // NULL the widgets head
    grid->wt_head = NULL;

    return grid;
}

void ui_grid_attach(grid_t *grid, widget_t *widget, int (*handler)(void *data), void *data)
{
    if (grid->wt_head == NULL)
    {
        grid->wt_head = widget;
        return;
    }

    widget_t *tmp = grid->wt_head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = widget;
}

widget_t *ui_button_new(const char *label)
{
    widget_t *wd = (widget_t *) malloc(sizeof(widget_t));
    wd->id = 11;
    wd->type = BUTTON;
    wd->label = label;

    return wd;
}

void ui_grid_free(grid_t *grid)
{
    free(grid->mtx);
    free(grid);
}
