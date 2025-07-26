#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <cstdint>
#include <drivers/screen.h>
#include <lib/ui_colors.h>

typedef struct ui_struct
{
    uint32_t navbar_height;  // navigation bar height
    uint32_t statbar_height; // status bar height
} ui_struct;

typedef struct window_t
{

} window_t;

typedef struct grid_t
{
    uint32_t cell_width;
    uint32_t cell_height;
    uint16_t *mtx;
} grid_t;

typedef struct widget_t
{

} widget_t;

enum
{
    WINDOW_DEFAULT = 1 << 0,
    WINDOW_FULL_BARS = 1 << 1,
    WINDOW_FULL_NO_BARS = 1 << 2,
    WINDOW_FULL_NO_NAVBAR = 1 << 3,
    WINDOW_FULL_NO_STATBAR = 1 << 4,
};

#define RTE rnd_to_even
int rnd_to_even(int n);

bool ui_init();
bool bar_init();
void bar_navigation();
void bar_status();
grid_t *ui_grid_new(const uint32_t rows, const uint32_t cols);

// Bootlogging
// revork to global func like linux
// when specify log_to(screen/serial/...)
#define BOOT_LVL_OK     0
#define BOOT_LVL_FAILED 1
#define BOOT_LVL_INFO   2

void bootlog(const char *log, uint8_t lvl);
void bootlogf(uint8_t l, const char *format, ...);

#endif
