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
void screen_fill_rect_p(int32_t x1, int32_t y1, int32_t x2, int32_t y2, uint32_t color)
{
    screen.fillRect(x1, y1, (x2 - x1), (x2 - x1), color);
}

void screen_draw_line(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color)
{
    screen.drawLine(xs, ys, xe, ye, color);
}

void screen_draw_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
                          uint32_t color)
{
    screen.drawTriangle(x1, y1, x2, y2, x3, y3, color);
}

void screen_fill_triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3,
                          uint32_t color)
{
    screen.fillTriangle(x1, y1, x2, y2, x3, y3, color);
}

void screen_draw_circle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    screen.drawCircle(x, y, r, color);
}

void screen_fill_circle(int32_t x, int32_t y, int32_t r, uint32_t color)
{
    screen.fillCircle(x, y, r, color);
}
