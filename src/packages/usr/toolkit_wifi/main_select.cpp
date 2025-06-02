#include <WiFi.h>
#include "kernel/usr/gui/gui.h"
#include "kernel/usr/apps/apps.h"
#include "kernel/dev/screen/screen.h"

void main_select_wifi(void *lp_param)
{
    int c = *(int *)lp_param;

    screen.fillScreen(TFT_BLACK);
    status_bar(WiFi.SSID(c) != "" ? WiFi.SSID(c) : WiFi.BSSIDstr(c));
    bottom_bar();

    GridView *grid = grid_init(7, 1);
    for (int i = 1; i < apps->count + 1; i++)
    {
        if (apps->list[i].category == "ToolkitWifi" || apps->list[i].category == "ToolkitWiFi")
            constructor(grid, apps->list[i].app_name, TILE_BUTTON, 2);
    }

    while (1)
    {
        String msg = handler(grid);
        static unsigned long bar_t = 0;

        if (msg == "EXIT") {
            delay(200);
            break;
        }
        if (msg != "")
        {
            for (int i = 1; i < apps->count + 1; i++)
            {
                if (msg == apps->list[i].app_name)
                {
                    apps->list[i].entry(lp_param);
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

void app_add_main_toolkit_wifi()
{
    app_add("SelectWifi", "MainToolkitWifi", main_select_wifi);
}
