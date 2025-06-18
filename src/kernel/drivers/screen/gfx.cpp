#include "TFT_eSPI.h"
#include <drivers/screen.h>

extern TFT_eSPI screen;

void screen_set_text_color(uint16_t color)
{
    screen.setTextColor(color);
}
