#include "drivers/lcd/generic.h"

void ui_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    lcd_set_cursor(x, y);
    lcd_set_data16(color);
}
