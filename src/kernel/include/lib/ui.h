#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
#include <drivers/screen.h>

// colors
#define TFT_GREY1     0x2985
#define TFT_GREY2     0x18c3
#define TFT_GREY3     0x9492
#define TFT_DARKGREY1 0x0861

#define BOOT_LVL_OK     0
#define BOOT_LVL_FAILED 1
#define BOOT_LVL_INFO   2

typedef struct ui_struct
{
    uint32_t h_navbar;  // navigation bar height
    uint32_t h_statbar; // status bar height
} ui_struct;

typedef struct window_t
{

} window_t;

typedef struct grid_t
{
    uint32_t blk_width;
    uint32_t blk_height;
    uint32_t blks_y;
    uint32_t blks_x;
} grid_t;

typedef struct widget_t
{

} widget_t;

bool ui_init();
bool bar_init();
void bar_navigation();
void bar_status();

// Bootlogging
void bootlog(const char *log, uint8_t lvl);
void bootlogf(uint8_t l, const char *format, ...);

#endif
