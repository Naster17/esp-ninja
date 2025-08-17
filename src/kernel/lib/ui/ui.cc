#include <drivers/screen.h>
#include <drivers/serial.h>
#include <drivers/touch.h>
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

void ui_draw(grid_t *grid)
{
    if (grid->wt_head == NULL)
        return; // maybe fix this shity do while

    widget_t *widget = grid->wt_head;
    do
    {
        int32_t y = (grid->cell_height * widget->row) + ui_st.statbar_height;
        int32_t h = grid->cell_height * widget->height;

        int32_t x = grid->cell_width * widget->col;
        int32_t w = grid->cell_width * widget->width;

        if (widget->row == 0)
            y = ui_st.statbar_height;
        if (widget->col == 0)
            x = 0;

        widget->renderer(x, y, w, h, widget);

    } while ((widget = widget->next) != NULL);
}

void ui_touch_handler(grid_t *grid, touch_state_t *st)
{
    widget_t *widget = grid->wt_head;
    do
    {
        int32_t y = (grid->cell_height * widget->row) + ui_st.statbar_height;
        int32_t h = grid->cell_height * widget->height;

        int32_t x = grid->cell_width * widget->col;
        int32_t w = grid->cell_width * widget->width;

        if (widget->row == 0)
            y = ui_st.statbar_height;
        if (widget->col == 0)
            x = 0;

        if (st->point.x < (x + w) && st->point.x > x && st->point.y < (y + h) && st->point.y > y)
        {
            serial_print(widget->label);
            widget->animator(x, y, w, h, widget);

        }

    } while ((widget = widget->next) != NULL);
}

void ui_run(grid_t *grid)
{
    ui_draw(grid);
    for (;;)
    {
        touch_state_t st = touch_get_state();
        if (st.state != TOUCH_NONE)
        {
            ui_touch_handler(grid, &st);
            // ui_draw(grid);
        }
    }
}
