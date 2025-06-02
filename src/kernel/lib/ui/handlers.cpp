#include "gui.h"
#include "kernel/dev/screen/screen.h"

int bar_handler()
{
    if (!touch.touched())
        return 0;

    // Debug for you
    // Serial.printf("Touch Pressed: x=%d, y=%d\n", t.x, t.y);
    // for (int i = 1; i < btn->count + 1; i++)
    // Serial.printf("%d: xs:%d ys:%d, xe:%d ye:%d, title:%s\n", i, btn->pos[i].xs, btn->pos[i].ys, btn->pos[i].xe, btn->pos[i].ye, btn->titles[i]);

    CYD28_TS_Point t = touch.getPointScaled();
    int32_t bt_start = TFT_WIDTH - (TFT_WIDTH / BACK_BUTTON_SIZE);
    screen.setTextSize(2);
    if (t.x > bt_start && t.x < SCREEN_WIDTH && t.y > 0 && t.y < screen.fontHeight(1))
    {
        return 1;
    }

    return 0;
}

String grid_handler(GridView *grid)
{
    if (!touch.touched())
        return "";

    CYD28_TS_Point t = touch.getPointScaled();

    for (int i = 1; i < grid->pos_count + 1; i++)
    {
        if (t.x > grid->pos[i].xs && t.x < grid->pos[i].xs + grid->tile_w && t.y > grid->pos[i].ys && t.y < grid->pos[i].ys + grid->tile_h)
        {
            animator(i, grid);
            return grid->pos[i].title;
        }
    }
    return "";
}

String handler(GridView *grid)
{
    String buttons = grid_handler(grid);
    if (buttons != "")
        return buttons;

    int bar = bar_handler();
    if (bar == 1)
        return "EXIT";

    return "";
}