#include <drivers/screen.h>

extern TFT_eSPI screen;

void screen_draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    screen.drawRect(x, y, w, h, color);
}
void screen_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color)
{
    screen.fillRect(x, y, w, h, color);
}

void screen_draw_line(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color)
{
    screen.drawLine(xs, ys, xe, ye, color);
}
