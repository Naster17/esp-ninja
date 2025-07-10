#ifndef LIB_UI_H
#define LIB_UI_H

#include <Arduino.h>
#include <TFT_eSPI.h>
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
    uint32_t blk_width;
    uint32_t blk_height;
} grid_t;

typedef struct widget_t
{

} widget_t;

bool ui_init();
bool bar_init();
void bar_navigation();
void bar_status();

// Bootlogging

#define BOOT_LVL_OK     0
#define BOOT_LVL_FAILED 1
#define BOOT_LVL_INFO   2

void bootlog(const char *log, uint8_t lvl);
void bootlogf(uint8_t l, const char *format, ...);

#endif
