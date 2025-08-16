#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <drivers/screen.h>
#include <drivers/touch.h>
#include <lib/ui_colors.h>

//
// Main Frame
//
typedef struct ui_struct
{
    uint32_t navbar_height;  // navigation bar height
    uint32_t statbar_height; // status bar height
} ui_struct;

enum
{
    WINDOW_DEFAULT = 1 << 0,
    WINDOW_FULL_BARS = 1 << 1,
    WINDOW_FULL_NO_BARS = 1 << 2,
    WINDOW_FULL_NO_NAVBAR = 1 << 3,
    WINDOW_FULL_NO_STATBAR = 1 << 4
};

typedef struct window_t
{

} window_t;

//
// Widgets
//
typedef struct widget_style
{
    int color_bg;
    int color_text;
    int color_frame;
} widget_style;

typedef enum widget_type
{
    BUTTON,
    LABEL,
    RADIO,
} widget_type;

typedef enum widget_event
{
    CLICKED,
    DOUBLE_CLICKED,
    HOLDED,
} widget_event;

typedef struct widget_t
{
    uint16_t id;
    widget_type type;
    widget_style *style;
    // button
    const char *label;
    int icon;
    widget_event event;
    int (*handler)(void *p);
    // w/h in row/cols like 1/1
    uint16_t row, col;
    uint16_t width, height;

    widget_t *next;
} widget_t;

widget_t *ui_button_new(const char *label);
void ui_widget_style_connect(widget_t *widget, widget_style *style);
void ui_drawer(int32_t x, int32_t y, int32_t w, int32_t h, widget_t widget);

//
// Grid
//
typedef struct grid_t
{
    uint16_t rows, cols;
    // cell sizes
    uint32_t cell_width;
    uint32_t cell_height;
    // widgets linked list
    widget_t *wt_head;
} grid_t;

void ui_grid_attach(grid_t *grid, widget_t *widget, int16_t row, int16_t col, int16_t w, int16_t h);
void ui_widget_connect(widget_t *widget, widget_event event, int (*handler)(void *p), void *data);
void ui_run(grid_t *grid);

//
// Other
//

#define RTE rnd_to_even
int rnd_to_even(int n);

void _mtx_set(grid_t *grid, size_t row, size_t col, uint16_t value);
uint16_t _mtx_get(grid_t *grid, size_t row, size_t col);

bool ui_init();
bool bar_init();
void bar_navigation();
void bar_status();
grid_t *ui_grid_new(const uint32_t rows, const uint32_t cols);
void ui_grid_free(grid_t *grid);

// Bootlogging
// revork to global func like linux
// when specify log_to(screen/serial/...)
#define BOOT_LVL_OK     0
#define BOOT_LVL_FAILED 1
#define BOOT_LVL_INFO   2

void bootlog(const char *log, uint8_t lvl);
void bootlogf(uint8_t l, const char *format, ...);

#endif
