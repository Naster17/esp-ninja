#include <drivers/screen.h>

extern TFT_eSPI screen;

void screen_print(const char *s)
{
    screen.print(s);
}

void screen_println(const char *s)
{
    screen.println(s);
}
