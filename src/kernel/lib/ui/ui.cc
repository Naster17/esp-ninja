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

void ui_drawer(int32_t x, int32_t y, int32_t w, int32_t h, widget_t *widget)
{
    if (widget->type == BUTTON)
    {
        screen_fill_rect(x, y, w, h, widget->style->frame_color);
        screen_fill_rect(x, y, w - 2, h - 2, widget->style->bg_color);
        // double upper frame
        screen_draw_line(x, y, (x + w) - 1, y, widget->style->notch_color);
        screen_draw_line(x, y + 1, (x + w) - 1, y + 1, widget->style->notch_color);
        // draw text
        screen_set_text_color(widget->style->font_color);
        screen_set_text_size(widget->style->font_size);
        int16_t font_width = screen_get_text_width(widget->label);
        int16_t font_height = screen_get_font_height();

        if (font_width > w && widget->style->font_type == font_adaptive)
        {
            screen_printfc(x, y, "%s", widget->label);
        }
        else
        {
            int16_t border = (w - font_width) / 2;
            int16_t border_top = (h - font_height) / 2;
            screen_printfc(x + border, y + border_top, "%s", widget->label);
        }
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
