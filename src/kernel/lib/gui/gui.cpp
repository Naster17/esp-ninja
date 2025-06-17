#include <lib/ui.h>
#include <drivers/screen.h>

GridView *grid_init(const int32_t lines, const int32_t rows)
{
    GridView *grid = (GridView *)malloc(sizeof(GridView));
    // for example redefine it if you want use vertical/horizontal
    // app insted off standart orientation screen layout
    grid->screen_h = SCREEN_HEIGHT;
    grid->screen_w = SCREEN_WIDTH;
    // with out setting text size it cant calc. it
    screen.setTextSize(2);
    grid->start_h = screen.fontHeight(1);
    screen.setTextSize(1);
    grid->end_h = screen.fontHeight(1);
    // malloc for positions
    grid->pos_count = 0;
    grid->lines = lines;
    grid->rows = rows;
    // Tiles
    grid->tile_w = grid->screen_w / rows;
    grid->tile_h = (grid->screen_h - (grid->end_h + grid->start_h)) / lines;
    // Pos
    grid->pos = (Positions *)calloc((lines * rows) + 1, sizeof(Positions));

    return grid;
}

GridView *grid_poly_init(GridView *grid, const int32_t lines, const int32_t rows)
{
    GridView *poly_grid = grid_init(lines, rows);
    poly_grid->start_h = grid->pos[grid->pos_count].ys + grid->tile_h;
    poly_grid->end_h = grid->end_h;

    poly_grid->tile_w = grid->screen_w / rows;
    poly_grid->tile_h = (grid->screen_h - (grid->end_h + grid->start_h + grid->tile_h)) / lines;
    return poly_grid;
}

void grid_deinit(GridView *grid)
{
    free((void *)grid);
    free((void *)grid->pos);
}

void grid_refresh(GridView *grid)
{
    screen.fillRect(0, grid->start_h, SCREEN_WIDTH, SCREEN_HEIGHT - (grid->end_h + grid->start_h), TFT_BLACK);
    int32_t font_h = (int32_t)screen.fontHeight(1);

    for (int c = 1; c < grid->pos_count + 1; c++)
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
        screen.fillRect(xs + 1, ys + 1, xe - 2, 4, TFT_GREY3);
        screen.fillRect(xs + 1, ys + 2, xe - 2, ye - 3, TFT_GREY2);

        screen.setTextColor(TFT_GREY3);
        screen.drawString(grid->pos[c].title, xs + ((bt_width - font_w) / 2), ys + ((bt_height - font_h) / 2) + 2);
    }
}

void constructor(GridView *grid, String title, Tiles type, int32_t font_size)
{
    grid->pos_count += 1;
    // if items count more then screen support
    if (grid->pos_count > (grid->rows * grid->lines))
        return;

    int32_t xs, ys, xe, ye;

    screen.setTextSize(font_size);
    int32_t font_w = (int32_t)screen.textWidth(title);
    int32_t font_h = (int32_t)screen.fontHeight(1);

    // initial item
    if (grid->pos_count == 1)
    {
        xs = 0;
        ys = grid->start_h;
    }
    // new line item
    else if ((grid->pos_count - 1) % grid->rows == 0)
    {
        xs = 0;
        ys = grid->pos[grid->pos_count - 1].ys + grid->tile_h;
    }
    // next item
    else
    {
        xs = grid->pos[grid->pos_count - 1].xs + grid->tile_w;
        ys = grid->pos[grid->pos_count - 1].ys;
    }

    xe = grid->tile_w;
    ye = grid->tile_h;

    switch (type)
    {
    case TILE_BUTTON:
        screen.drawRect(xs, ys, xe, ye, TFT_DARKGREY1);
        screen.fillRect(xs + 1, ys + 1, xe - 2, 2, TFT_GREY3);
        screen.fillRect(xs + 1, ys + 2, xe - 2, ye - 3, TFT_GREY2);

        screen.setTextColor(TFT_GREY3, TFT_GREY2, false);
        screen.drawString(title, xs + ((grid->tile_w - font_w) / 2), ys + ((grid->tile_h - font_h) / 2) + 2);
        break;

    case TILE_INPUT:
        screen.drawRect(xs, ys, xe, ye, TFT_GREY2);
        screen.drawRect(xs + 1, ys + 1, xe - 2, ye - 2, TFT_DARKGREY1);
        screen.drawRect(xs + 2, ys + 2, xe - 3, ye - 3, TFT_DARKGREY1);
        screen.setTextColor(TFT_WHITE, TFT_BLACK, true);
        screen.drawString(title, xs + ((grid->tile_w - font_w) / 2), ys + ((grid->tile_h - font_h) / 2) + 2);
        break;

    case TILE_OUTPUT:
        screen.drawRect(xs, ys, xe, ye, TFT_GREY2);
        screen.drawRect(xs + 1, ys + 1, xe - 2, ye - 2, TFT_DARKGREY1);
        screen.drawRect(xs + 2, ys + 2, xe - 3, ye - 3, TFT_DARKGREY1);
        screen.setTextColor(TFT_WHITE);
        screen.drawString(title, xs + 2, ys + 2);
        break;

    case TILE_EMPTY:
        screen.drawRect(xs, ys, xe, ye, TFT_BLACK);
        break;
    }

    grid->pos[grid->pos_count].font_size = font_size;
    grid->pos[grid->pos_count].title = title;
    grid->pos[grid->pos_count].type = type;

    grid->pos[grid->pos_count].xs = xs;
    grid->pos[grid->pos_count].ys = ys;
    grid->pos[grid->pos_count].xe = xe;
    grid->pos[grid->pos_count].ye = ye;
}

void animator(int32_t c, GridView *grid)
{

    // Animate Style
    switch (grid->pos[c].type)
    {
    case TILE_BUTTON:
        _animator_button(c, grid);
        break;
    case TILE_INPUT:
        delay(250);
        break;
    default:
        break;
    }
}

struct compose compositor(GridView *grid, String title, uint8_t font_size)
{
    int32_t xs, ys, xe, ye;

    screen.setTextSize(font_size);
    int32_t font_w = (int32_t)screen.textWidth(title);
    int32_t font_h = (int32_t)screen.fontHeight(1);

    // initial item
    if (grid->pos_count == 1)
    {
        xs = 0;
        ys = grid->start_h;
    }
    // new line item
    else if ((grid->pos_count - 1) % grid->rows == 0)
    {
        xs = 0;
        ys = grid->pos[grid->pos_count - 1].ys + grid->tile_h;
    }
    // next item
    else
    {
        xs = grid->pos[grid->pos_count - 1].xs + grid->tile_w;
        ys = grid->pos[grid->pos_count - 1].ys;
    }

    xe = grid->tile_w;
    ye = grid->tile_h;

    return (struct compose){.xs = xs, .ys = ys, .xe = xe, .ye = ye};
}

int _updater(GridView *grid, struct compose cm, bool status, String title, Tiles type, uint8_t font_size)
{
    grid->pos[grid->pos_count].id = grid->pos_count;
    grid->pos[grid->pos_count].status = status;
    grid->pos[grid->pos_count].title = title;
    grid->pos[grid->pos_count].type = type;
    grid->pos[grid->pos_count].font_size = font_size;
    grid->pos[grid->pos_count].xs = cm.xs;
    grid->pos[grid->pos_count].ys = cm.ys;
    grid->pos[grid->pos_count].xe = cm.xe;
    grid->pos[grid->pos_count].ye = cm.ye;

    return grid->pos_count;
}
