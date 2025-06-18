#ifndef SCREEN_DRIVER_H
#define SCREEN_DRIVER_H
#undef ILI9341_DRIVER

#include <Arduino.h>
#include <TFT_eSPI.h>

extern int32_t SCREEN_HEIGHT;
extern int32_t SCREEN_WIDTH;

//
// Core
//

// Set initializy SPI to work with screen
int screen_init();

// Rotate screen
void screen_rotate(int r);
void screen_clear();

//
// Print
//

// Default formated output with %
void screen_printf(const char *format, ...);

// Base const char *output
void screen_print(const char *s);

// Print with new line, Arduino Framework madnes
void screen_println(const char *s);
void screen_printfc(int32_t x, int32_t y, const char *format, ...);

//
// GFX
//
void screen_set_text_color(uint16_t color);
void screen_set_text_size(uint8_t size);
int16_t screen_get_font_height();

void screen_draw_line(int32_t xs, int32_t ys, int32_t xe, int32_t ye, uint32_t color);
void screen_draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

void screen_fill_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint32_t color);

#endif // SCREEN_DRIVER_H
