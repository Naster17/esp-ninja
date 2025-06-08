#ifndef DRIVER_CYD28
#define DRIVER_CYD28

#include "driver/spi_master.h"
#include "stdint.h"

#define LCD_HOST VSPI_HOST
#define DMA_CHAN 1

#define PIN_NUM_MISO 12
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  14
#define PIN_NUM_CS   15

#define PIN_NUM_DC   2
#define PIN_NUM_RST  -1
#define PIN_NUM_BCKL 21

#define LCD_DISPLAY_ORIENTATION_PORTRAIT           0
#define LCD_DISPLAY_ORIENTATION_PORTRAIT_INVERTED  1
#define LCD_DISPLAY_ORIENTATION_LANDSCAPE          2
#define LCD_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED 3

extern uint16_t LCD_Width;
extern uint16_t LCD_Height;
extern uint8_t LCD_Orientation;

#define WHITE   0xFFFF
#define BLACK   0x0000
#define BLUE    0x001F
#define BRED    0XF81F
#define GRED    0XFFE0
#define GBLUE   0X07FF
#define RED     0xF800
#define MAGENTA 0xF81F
#define GREEN   0x07E0
#define CYAN    0x7FFF
#define YELLOW  0xFFE0
#define BROWN   0XBC40
#define BRRED   0XFC07
#define GRAY    0X8430

#define DARKBLUE  0X01CF
#define LIGHTBLUE 0X7D7C
#define GRAYBLUE  0X5458

#define LIGHTGREEN 0X841F
#define LIGHTGRAY  0XEF5B
#define LGRAY      0XC618

#define LGRAYBLUE 0XA651
#define LBBLUE    0X2B12

#define PARALLEL_LINES 16

bool lcd_init();

void lcd_spi_pre_transfer_callback(spi_transaction_t *t);
void lcd_set_cmd(const uint8_t cmd);
void lcd_set_data(const uint8_t *data, int len);
void lcd_set_data16(uint16_t data);
void lcd_set_windows(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye);
void lcd_set_cursor(uint16_t xpos, uint16_t ypos);
void lcd_clear(uint16_t color);
void lcd_set_orientation(uint8_t orientation);

#endif
