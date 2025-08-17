#include <drivers/screen.h>
#include <lib/ui.h>

widget_t *ui_button_new(const char *label)
{
    widget_t *widget = (widget_t *) malloc(sizeof(widget_t));
    widget->id = 11;
    widget->type = BUTTON;
    widget->label = label;

    widget_style *style = (widget_style *) malloc(sizeof(widget_style));
    style->bg_color = COLOR_GREY_3;
    style->font_color = COLOR_GREY_5;
    style->notch_color = COLOR_GREY_4;
    style->frame_color = COLOR_GREY_1;
    style->font_type = font_adaptive;
    style->font_size = 2;

    widget->style = style;

    widget->next = NULL;
    return widget;
}
