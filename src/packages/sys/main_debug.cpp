
#include "kernel/usr/gui/gui.h"
#include "kernel/usr/apps/apps.h"
#include "kernel/dev/screen/screen.h"

void main_debug(void *lp_param)
{
    screen.fillScreen(TFT_BLACK);
    status_bar("Debug");
    bottom_bar();

    GridView *grid = grid_init(5, 2);
    // Classic category search
    for (int i = 1; i < apps->count + 1; i++)
    {
        if (apps->list[i].category == "Debug")
            constructor(grid, apps->list[i].app_name, TILE_BUTTON, 2);
    }

    unsigned long bar_t = 0;
    while (1)
    {
        String msg = handler(grid);

        if (msg == "EXIT")
            break;

        if (msg != "")
        {
            for (int i = 1; i < apps->count + 1; i++)
            {
                if (msg == apps->list[i].app_name)
                {
                    apps->list[i].entry(NULL);
                    grid_refresh(grid);
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

void app_add_debug()
{
    app_add("Debug", "System", main_debug);
}