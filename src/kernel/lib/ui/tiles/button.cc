#include <drivers/screen.h>
#include <drivers/serial.h>
#include <lib/ui.h>

int _default_renderer(int32_t x, int32_t y, int32_t w, int32_t h, widget_t *widget)
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
    return 0;
}
int _default_animator(int32_t x, int32_t y, int32_t w, int32_t h, widget_t *widget)
{
    screen_fill_rect(x, y, w, h, widget->style->frame_color);
    screen_fill_rect(x, y, w - 2, h - 2, COLOR_GREY_2);
    // double upper frame
    screen_draw_line(x, y, (x + w) - 1, y, COLOR_GREY_3);
    screen_draw_line(x, y + 1, (x + w) - 1, y + 1, COLOR_GREY_3);
    // draw text
    screen_set_text_color(COLOR_GREY_4);
    screen_set_text_size(widget->style->font_size);
    int16_t font_width = screen_get_text_width(widget->label);
    int16_t font_height = screen_get_font_height();

    if (font_width > w && widget->style->font_type == font_adaptive)
    {
        // add adaptive font reduce
        screen_printfc(x, y, "%s", widget->label);
    }
    else
    {
        int16_t border = (w - font_width) / 2;
        int16_t border_top = (h - font_height) / 2;
        screen_printfc(x + border, y + border_top, "%s", widget->label);
    }
    delay(150);
    _default_renderer(x, y, w, h, widget);
    // add Label sortner Like Blue...
    return 0;
}

widget_t *ui_button_new(const char *label)
{
    widget_t *widget = (widget_t *) malloc(sizeof(widget_t));
    widget->id = 11;
    widget->type = BUTTON;
    widget->label = label;

    widget_style_t *style = (widget_style_t *) malloc(sizeof(widget_style_t));
    style->bg_color = COLOR_GREY_3;
    style->font_color = COLOR_GREY_5;
    style->notch_color = COLOR_GREY_4;
    style->frame_color = COLOR_GREY_1;
    style->font_type = font_adaptive;
    style->font_size = 2;
    widget->style = style;

    widget->renderer = _default_renderer;
    widget->animator = _default_animator;

    widget->events = NULL;

    widget->next = NULL;
    return widget;
}
