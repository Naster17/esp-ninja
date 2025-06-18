#include <drivers/screen.h>
#include <lib/ui.h>

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
