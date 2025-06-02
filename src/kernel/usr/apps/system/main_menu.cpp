
#include "kernel/usr/gui/gui.h"
#include "kernel/usr/apps/apps.h"
#include "kernel/dev/screen/screen.h"

void main_menu(void *lp_param)
{
    screen.fillScreen(TFT_BLACK);
    status_bar("Ninja32");
    bottom_bar();

    GridView *grid = grid_init(4, 2);

    grid_add_button(grid, "WiFi", 2);
    grid_add_button(grid, "Bluetooth", 2);

    grid_add_button(grid, "Apps", 2);
    grid_add_button(grid, "Community", 2);

    grid_add_button(grid, "Utils", 2);
    grid_add_button(grid, "Other", 2);

    grid_add_button(grid, "Debug", 2);
    grid_add_button(grid, "Options", 2);

    while (1)
    {
        String msg = handler(grid);
        static unsigned long bar_t = 0;

        if (msg != "")
        {
            for (int i = 1; i < apps->count + 1; i++)
            {
                if (msg == apps->list[i].app_name)
                {
                    apps->list[i].entry(NULL);
                    grid_refresh(grid);
                    status_bar("Ninja32");
                    break;
                }
            }
        }

        if (millis() - bar_t > 5000)
        {
            bottom_bar();
            bar_t = millis();
        }
        delay(50);
    }

    grid_deinit(grid);
}

void app_add_main()
{
    app_add("Main", "", main_menu);
}