#include <drivers/screen.h>
#include <lib/ui.h>

void bootlog(String log, uint8_t lvl)
{
    if (lvl == BOOT_LVL_OK)
    {
        screen.print("[  ");
        screen.setTextColor(TFT_GREEN);
        screen.print("OK");
        screen.setTextColor(TFT_WHITE);
        screen.print("  ]");
        screen.print(" ");
        screen.println(log);
    }
    else if (lvl == BOOT_LVL_FAILED)
    {
        screen.print("[");
        screen.setTextColor(TFT_RED);
        screen.print("FAILED");
        screen.setTextColor(TFT_WHITE);
        screen.print("]");
        screen.print(" ");
        screen.println(log);
    }
    else if (lvl == BOOT_LVL_INFO)
    {
        screen.print("[ ");
        screen.setTextColor(TFT_BLUE);
        screen.print("INFO");
        screen.setTextColor(TFT_WHITE);
        screen.print(" ]");
        screen.print(" ");
        screen.println(log);
    }
}
