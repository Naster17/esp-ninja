#include <drivers/screen.h>
#include <lib/ui.h>

int grid_add_output(GridView *grid, String title, uint8_t text_position, uint8_t font_size)
{
    grid->pos_count += 1;
    // if items count more then screen support
    if (grid->pos_count > (grid->rows * grid->lines))
        return -1;

    struct compose cm = compositor(grid, title, font_size);

    screen.drawRect(cm.xs, cm.ys, cm.xe, cm.ye, TFT_GREY2);
    screen.drawRect(cm.xs + 1, cm.ys + 1, cm.xe - 2, cm.ye - 2, TFT_DARKGREY1);
    screen.drawRect(cm.xs + 2, cm.ys + 2, cm.xe - 3, cm.ye - 3, TFT_DARKGREY1);
    screen.setTextColor(TFT_WHITE);
    screen.setTextSize(font_size);

    int line_index = -1;
    int str_count = 0;
    for (int i = 0; i < title.length(); i++)
    {
        if (title.charAt(i) == '\n')
        {
            String new_line = title.substring(line_index + 1, i + 1);

            if (text_position == TEXT_POSITION_TOP_LEFT)
                screen.setCursor(cm.xs + 5, cm.ys + (str_count * screen.fontHeight(1)) + 5);
            else if (text_position == TEXT_POSITION_CENTER)
                screen.setCursor(cm.xs + ((grid->tile_w - screen.textWidth(new_line)) / 2),
                                 cm.ys + (str_count * screen.fontHeight(1)) + 5);

            screen.print(new_line);
            line_index = i;
            str_count += 1;
        }
    }
    if (line_index != title.length() - 1)
    {
        String new_line = title.substring(line_index + 1);

        if (text_position == TEXT_POSITION_TOP_LEFT)
            screen.setCursor(cm.xs + 5, cm.ys + (str_count * screen.fontHeight(1)) + 5);
        else if (text_position == TEXT_POSITION_CENTER)
            screen.setCursor(cm.xs + ((grid->tile_w - screen.textWidth(new_line)) / 2),
                             cm.ys + (str_count * screen.fontHeight(1)) + 5);

        screen.print(new_line);
    }

    return _updater(grid, cm, 0, title, TILE_OUTPUT, font_size);
}

int grid_output_write(GridView *grid, int id, String text, uint8_t text_position, uint8_t font_size,
                      bool append)
{
    static String l_text;
    if (append)
        l_text = grid->pos[id].title + "\n" + text;
    else
        l_text = text;

    screen.fillRect(grid->pos[id].xs + 2, grid->pos[id].ys + 2, grid->pos[id].xe - 4,
                    grid->pos[id].ye - 4, TFT_BLACK);
    screen.setTextColor(TFT_WHITE);

    int line_index = -1;
    int str_count = 0;
    for (int i = 0; i < l_text.length(); i++)
    {
        if (l_text.charAt(i) == '\n')
        {
            String new_line = l_text.substring(line_index + 1, i + 1);

            if (text_position == TEXT_POSITION_TOP_LEFT)
                screen.setCursor(grid->pos[id].xs + 5,
                                 grid->pos[id].ys + (str_count * screen.fontHeight(1)) + 5);
            else if (text_position == TEXT_POSITION_CENTER)
                screen.setCursor(grid->pos[id].xs +
                                     ((grid->tile_w - screen.textWidth(new_line)) / 2),
                                 grid->pos[id].ys + (str_count * screen.fontHeight(1)) + 5);

            screen.print(new_line);
            line_index = i;
            str_count += 1;
        }
    }
    if (line_index != l_text.length() - 1)
    {
        String new_line = l_text.substring(line_index + 1);

        if (text_position == TEXT_POSITION_TOP_LEFT)
            screen.setCursor(grid->pos[id].xs + 5,
                             grid->pos[id].ys + (str_count * screen.fontHeight(1)) + 5);
        else if (text_position == TEXT_POSITION_CENTER)
            screen.setCursor(grid->pos[id].xs + ((grid->tile_w - screen.textWidth(new_line)) / 2),
                             grid->pos[id].ys + (str_count * screen.fontHeight(1)) + 5);

        screen.print(new_line);
    }

    return 0;
}
