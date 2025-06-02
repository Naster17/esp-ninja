#include <drivers/led.h>
#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

void flashlight_app(void *lp_param)
{
    screen.fillScreen(TFT_BLACK);
    status_bar("FlashLight v2");
    bottom_bar();

    GridView *rgb = grid_init(4, 3);
    constructor(rgb, "R", TILE_BUTTON, 2);
    constructor(rgb, "G", TILE_BUTTON, 2);
    constructor(rgb, "B", TILE_BUTTON, 2);

    GridView *btns = grid_poly_init(rgb, 2, 1);
    constructor(btns, "ON", TILE_BUTTON, 3);
    constructor(btns, "OFF", TILE_BUTTON, 3);

    bool r = 0;
    bool g = 0;
    bool b = 0;

    while (1)
    {
        String btns_h = handler(btns);
        String rgb_h = handler(rgb);

        if (rgb_h == "EXIT")
            break;

        if (btns_h == "ON")
            set_state(1, 1, 1);

        else if (btns_h == "OFF")
        {
            r = 0;
            g = 0;
            b = 0;
            set_state(0, 0, 0);
        }

        if (rgb_h == "R")
        {
            r = !r;
            set_state(r, g, b);
        }
        else if (rgb_h == "G")
        {
            g = !g;
            set_state(r, g, b);
        }
        else if (rgb_h == "B")
        {
            b = !b;
            set_state(r, g, b);
        }

        delay(50);
    }

    grid_deinit(rgb);
    grid_deinit(btns);
}

void app_add_flashlight()
{
    app_add("FlashLight", "Apps", flashlight_app);
}
