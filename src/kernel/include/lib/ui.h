#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <cstdint>
#include <drivers/screen.h>
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
typedef enum widget_type
{
    BUTTON,
    LABEL,
    RADIO,
} widget_type;

typedef struct widget_t
{
    uint16_t id;
    widget_type type;
    const char *label;
    widget_t *next;
} widget_t;

widget_t *ui_button_new(const char *label);

//
// Grid
//
typedef struct grid_t
{
    uint16_t cols;
    uint16_t rows;
    // cell sizes
    uint32_t cell_width;
    uint32_t cell_height;
    // widgets linked list
    widget_t *wt_head;
} grid_t;

void ui_grid_attach(grid_t *grid, widget_t *widget, int (*handler)(void *data), void *data);

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
