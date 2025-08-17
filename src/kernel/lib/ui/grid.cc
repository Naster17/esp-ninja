#include <drivers/screen.h>
#include <lib/ui.h>

extern ui_struct ui_st;

grid_t *ui_grid_new(const uint32_t rows, const uint32_t cols)
{
    grid_t *grid = (grid_t *) malloc(sizeof(grid_t));
    // allocate rows cols
    grid->cols = cols;
    grid->rows = rows;

    // allocate cell size h/w
    grid->cell_width = SCREEN_WIDTH / cols;
    grid->cell_height = (SCREEN_HEIGHT - (ui_st.navbar_height + ui_st.statbar_height)) / rows;

    // NULL the widgets head
    grid->wt_head = NULL;

    return grid;
}

void ui_grid_attach(grid_t *grid, widget_t *widget, int16_t row, int16_t col, int16_t w, int16_t h)
{
    // positioning widget
    widget->row = row;
    widget->col = col;
    widget->width = w;
    widget->height = h;

    if (grid->wt_head == NULL)
    {
        grid->wt_head = widget;
        return;
    }

    widget_t *tmp = grid->wt_head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = widget;
}

void ui_grid_free(grid_t *grid)
{
    widget_t *tmp;
    widget_t *current = grid->wt_head;
    while (current != NULL)
    {
        tmp = current;
        current = current->next;

        if (tmp->style != NULL)
            free(tmp->style);

        free(tmp);
    }
    grid->wt_head = NULL;
    free(grid);
}
