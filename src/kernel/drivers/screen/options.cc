#include <drivers/screen.h>

extern TFT_eSPI screen;

void screen_set_text_color(uint16_t color)
{
    screen.setTextColor(color);
}

void screen_set_text_size(uint8_t size)
{
    screen.setTextSize(size);
}

int16_t screen_get_font_height()
{
    return screen.fontHeight();
}

int16_t screen_get_text_width(const char *s)
{
    return screen.textWidth(s);
}
