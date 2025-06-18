#ifndef SCREEN_DRIVER_H
#define SCREEN_DRIVER_H
#undef ILI9341_DRIVER

#include <Arduino.h>
#include <TFT_eSPI.h>

extern int32_t SCREEN_HEIGHT;
extern int32_t SCREEN_WIDTH;

bool screen_init();
void screen_rotate(int r);
void screen_print(const char *s);
void screen_println(const char *s);
void screen_set_text_color(uint16_t color);

#endif // SCREEN_DRIVER_H
