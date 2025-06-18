#include <cstdlib>
#include <drivers/screen.h>
#include <stdarg.h>

extern TFT_eSPI screen;

void screen_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args) + 1;
    char *buffer = (char *) malloc(size);
    vsnprintf(buffer, size, format, args);
    va_end(args);
    // flush to screen
    screen_print(buffer);
    free(buffer);
}

void screen_print(const char *s)
{
    screen.print(s);
}

void screen_println(const char *s)
{
    screen.println(s);
}

void screen_printfc(int32_t x, int32_t y, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args) + 1;
    char *buffer = (char *) malloc(size);
    vsnprintf(buffer, size, format, args);
    va_end(args);
    // flush to screen
    screen.setCursor(x, y);
    screen_print(buffer);

    free(buffer);
}
