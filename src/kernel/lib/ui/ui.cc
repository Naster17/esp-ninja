#include "lib/ui_colors.h"
#include <cstdint>
#include <cstdlib>
#include <drivers/screen.h>
#include <drivers/serial.h>
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
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    // allocate rows cols
    grid->cols = cols;
    grid->rows = rows;

    // allocate cell size h/w
    grid->cell_width = SCREEN_WIDTH / cols;
    grid->cell_height = SCREEN_HEIGHT / rows;

    // NULL the widgets head
    grid->wt_head = NULL;

    return grid;
}
void ui_widget_connect(widget_t *widget, widget_event event, int (*handler)(void *p), void *data)
{
    // wewe
    // CREATE hiden event struct to connect multiple events to one widget
}

void ui_widget_style_connect(widget_t *widget, widget_style *style)
{
    // wewe
}

// fuck start with 0, 0, IM write 3/3 row/cols I get 3 cols and 3 rows
void ui_grid_attach(grid_t *grid, widget_t *widget, int16_t row, int16_t col, int16_t w, int16_t h)
{
    // positioning widget
    widget->row = row;
    widget->col = col;
    widget->width = w;
    widget->height = h;

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
    // wd->style = NULL;
    wd->next = NULL;

    return wd;
}

//
// Main Drawer
//
void ui_run(grid_t *grid)
{
    widget_t *widget = grid->wt_head;
    while (widget->next != NULL)
    {

        widget = widget->next;
    }
}

void ui_grid_free(grid_t *grid)
{
    widget_t *tmp;
    widget_t *current = grid->wt_head;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    grid->wt_head = NULL;
    free(grid);
}
