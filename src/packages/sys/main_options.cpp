#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

void main_options(void *lp_param)
{
    screen.fillScreen(TFT_BLACK);
    status_bar("Options");
    bottom_bar();

    GridView *grid = grid_init(6, 2);
    for (int i = 1; i < apps->count + 1; i++)
    {
        if (apps->list[i].category == "Options")
            constructor(grid, apps->list[i].app_name, TILE_BUTTON, 2);
    }

    while (1)
    {
        String msg = handler(grid);
        static unsigned long bar_t = 0;

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

void app_add_options()
{
    app_add("Options", "System", main_options);
}
