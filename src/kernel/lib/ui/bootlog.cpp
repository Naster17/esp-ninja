#include <lib/ui.h>
#include <stdarg.h>

#include <drivers/screen.h>

void bootlogf(uint8_t l, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    int size = vsnprintf(nullptr, 0, format, args) + 1;
    char *buffer = (char *) malloc(size);
    vsnprintf(buffer, size, format, args);
    va_end(args);
    // bootlog
    bootlog(buffer, l);
    free(buffer);
}

void bootlog(const char *log, uint8_t lvl)
{
    if (lvl == BOOT_LVL_OK)
    {
        screen_print("[  ");
        screen_set_text_color(TFT_GREEN);
        screen_print("OK");
        screen_set_text_color(TFT_WHITE);
        screen_print("  ]");
        screen_print(" ");
        screen_println(log);
    }
    else if (lvl == BOOT_LVL_FAILED)
    {
        screen_print("[");
        screen_set_text_color(TFT_RED);
        screen_print("FAILED");
        screen_set_text_color(TFT_WHITE);
        screen_print("]");
        screen_print(" ");
        screen_println(log);
    }
    else if (lvl == BOOT_LVL_INFO)
    {
        screen_print("[ ");
        screen_set_text_color(TFT_BLUE);
        screen_print("INFO");
        screen_set_text_color(TFT_WHITE);
        screen_print(" ]");
        screen_print(" ");
        screen_println(log);
    }
}
