#ifndef DRIVER_CYD28
#define DRIVER_CYD28

#ifndef __LCD_H__
#define __LCD_H__
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

#define LCD_DISPLAY_ORIENTATION_PORTRAIT           0 // 纵向
#define LCD_DISPLAY_ORIENTATION_PORTRAIT_INVERTED  1 // 纵向翻转
#define LCD_DISPLAY_ORIENTATION_LANDSCAPE          2 // 横向
#define LCD_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED 3 // 横向翻转

extern uint16_t LCD_Width;       // LCD 宽度
extern uint16_t LCD_Height;      // LCD 高度
extern uint8_t  LCD_Orientation; // 默认纵向

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

#define LGRAYBLUE 0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE    0X2B12 // 浅棕蓝色(选择条目的反色)

// To speed up transfers, every SPI transfer sends a bunch of lines. This define specifies how many.
// More means more memory use, but less overhead for setting up / finishing transfers. Make sure 240
// is dividable by this.
#define PARALLEL_LINES 16

void lcd_spi_pre_transfer_callback(spi_transaction_t *t);

uint32_t LCD_Get_ID(void);                         // 获取屏幕驱动芯片ID
void     LCD_Set_Orientation(uint8_t orientation); // 设置屏幕方向
void     LCD_Clear(uint16_t Color);                // 清屏指定颜色
void     LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd); // 设置窗口

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos); // 设置光标位置

#endif

bool lcd_init();

#endif
