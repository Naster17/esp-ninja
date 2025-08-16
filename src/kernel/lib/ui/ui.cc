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
    grid->cell_height = (SCREEN_HEIGHT - (ui_st.navbar_height + ui_st.statbar_height)) / rows;

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
    widget_style *style = (widget_style *) malloc(sizeof(widget_style));
    style->color_bg = COLOR_GREY_5;
    style->color_text = COLOR_GREY_1;
    style->color_frame = COLOR_GREY_2;
    wd->style = style;

    wd->next = NULL;
    return wd;
}

//
// Main Drawer
//

void ui_drawer(int32_t x, int32_t y, int32_t w, int32_t h, widget_t *widget)
{
    if (widget->type == BUTTON)
    {
        screen_fill_rect(x, y, w, h, widget->style->color_bg);
        // double upper frame
        screen_draw_line(x, y, (x + w) - 1, y, widget->style->color_frame);
        screen_draw_line(x, y + 1, (x + w) - 1, y + 1, widget->style->color_frame);
    }
}

void ui_run(grid_t *grid)
{
    if (grid->wt_head == NULL)
        return; // maybe fix this shity do while

    widget_t *widget = grid->wt_head;
    do
    {
        int32_t x, y;
        int32_t w, h;

        y = (grid->cell_height * widget->row) + ui_st.statbar_height;
        h = grid->cell_height;
        if (widget->row == 0)
        {
            y = ui_st.statbar_height;
            h = grid->cell_height;
        }
        x = grid->cell_width * widget->col;
        w = grid->cell_width;
        if (widget->col == 0)
        {
            x = 0;
            w = grid->cell_width;
        }
        ui_drawer(x, y, w * widget->width, h * widget->height, widget);

    } while ((widget = widget->next) != NULL);
}

void ui_grid_free(grid_t *grid)
{
    widget_t *tmp;
    widget_t *current = grid->wt_head;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;

        if (tmp->style != NULL)
            free(tmp->style);

        free(tmp);
    }
    grid->wt_head = NULL;
    free(grid);
}
