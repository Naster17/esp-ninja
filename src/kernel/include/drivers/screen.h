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

//
// Print
//

// Default formated output with %
void screen_printf(const char *format, ...);

// Base const char *output
void screen_print(const char *s);

// Print with new line, Arduino Framework madnes
void screen_println(const char *s);

//
// GFX
//
void screen_set_text_color(uint16_t color);

#endif // SCREEN_DRIVER_H
