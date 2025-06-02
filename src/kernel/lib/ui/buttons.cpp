#include "gui.h"
#include "kernel/dev/screen/screen.h"

void grid_add_button(GridView *grid, String title, uint8_t font_size)
{
    grid->pos_count += 1;
    // if items count more then screen support
    if ((grid->pos_count) > (grid->rows * grid->lines))
        return;

    struct compose cm = compositor(grid, title, font_size);

    screen.drawRect(cm.xs, cm.ys, cm.xe, cm.ye, TFT_DARKGREY1);
    screen.fillRect(cm.xs + 1, cm.ys + 1, cm.xe - 2, 2, TFT_GREY3);
    screen.fillRect(cm.xs + 1, cm.ys + 2, cm.xe - 2, cm.ye - 3, TFT_GREY2);

    screen.setTextColor(TFT_GREY3);
    screen.setTextSize(font_size);
    screen.drawString(title, cm.xs + ((grid->tile_w - screen.textWidth(title)) / 2), cm.ys + ((grid->tile_h - screen.fontHeight(1)) / 2) + 2);

    _updater(grid, cm, 0, title, TILE_BUTTON, font_size);
}

void _animator_button(int32_t c, GridView *grid)
{
    screen.setTextSize(grid->pos[c].font_size);
    int32_t font_w = (int32_t)screen.textWidth(grid->pos[c].title);
    int32_t font_h = (int32_t)screen.fontHeight(1);

    int32_t bt_height = (grid->screen_h - (grid->end_h + grid->start_h)) / grid->lines;
    int32_t bt_width = grid->screen_w / grid->rows;

    int32_t xs = grid->pos[c].xs;
    int32_t ys = grid->pos[c].ys;
    int32_t xe = grid->pos[c].xe;
    int32_t ye = grid->pos[c].ye;

    screen.drawRect(xs, ys, xe, ye, TFT_DARKGREY1);
    screen.fillRect(xs + 1, ys + 1, xe - 2, 4, TFT_GREY2);
    screen.fillRect(xs + 1, ys + 2, xe - 2, ye - 3, TFT_DARKGREY1);

    screen.setTextColor(TFT_GREY);
    screen.drawString(grid->pos[c].title, xs + ((bt_width - font_w) / 2), ys + ((bt_height - font_h) / 2) + 2);

    delay(250);

    // Back to style
    screen.drawRect(xs, ys, xe, ye, TFT_DARKGREY1);
    screen.fillRect(xs + 1, ys + 1, xe - 2, 4, TFT_GREY3);
    screen.fillRect(xs + 1, ys + 2, xe - 2, ye - 3, TFT_GREY2);

    screen.setTextColor(TFT_GREY3);
    screen.drawString(grid->pos[c].title, xs + ((bt_width - font_w) / 2), ys + ((bt_height - font_h) / 2) + 2);
}