#include "drivers/lcd/cyd28.h"
#include "driver/gpio.h"
#include "freertos/task.h"
#include "stdint.h"
#include "string.h"

typedef struct
{
    uint8_t cmd;
    uint8_t data[16];
    uint8_t databytes;
    // No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
} lcd_init_cmd_t;

spi_device_handle_t lcd_spi_handle;

uint16_t lcd_width = 240;
uint16_t lcd_height = 320;
uint8_t LCD_Orientation = LCD_DISPLAY_ORIENTATION_PORTRAIT;

void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    uintptr_t temp = (uintptr_t) t->user;         // Cast to uintptr_t first
    uint32_t dc = (uint32_t) (temp & 0xFFFFFFFF); // Mask to ensure it fits in 32 bits
    gpio_set_level(PIN_NUM_DC, dc);               // setting lvl
}

void lcd_set_cmd(const uint8_t cmd)
{
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8;
    t.tx_buffer = &cmd;
    t.user = (void *) 0;

    esp_err_t ret = spi_device_polling_transmit(lcd_spi_handle, &t);
    assert(ret == ESP_OK);
}

void lcd_set_data(const uint8_t *data, int len)
{
    if (len <= 0)
        return;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = len * 8;
    t.tx_buffer = data;
    t.user = (void *) 1;

    esp_err_t ret = spi_device_polling_transmit(lcd_spi_handle, &t);
    assert(ret == ESP_OK);
}

void lcd_set_data16(uint16_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    uint8_t dataBuf[2] = {0, 0};
    dataBuf[0] = data >> 8;
    dataBuf[1] = data & 0xFF;
    memset(&t, 0, sizeof(t));
    t.length = 2 * 8;
    t.tx_buffer = dataBuf;
    t.user = (void *) 1;
    ret = spi_device_polling_transmit(lcd_spi_handle, &t);
    assert(ret == ESP_OK);
}

void lcd_set_windows(uint16_t xs, uint16_t ys, uint16_t xe, uint16_t ye)
{
    uint8_t databuf[4] = {0, 0, 0, 0};
    databuf[0] = xs >> 8;
    databuf[1] = 0xFF & xs;
    databuf[2] = xe >> 8;
    databuf[3] = 0xFF & xe;
    lcd_set_cmd(0x2A);
    lcd_set_data(databuf, 4);

    databuf[0] = ys >> 8;
    databuf[1] = 0xFF & ys;
    databuf[2] = ye >> 8;
    databuf[3] = 0xFF & ye;
    lcd_set_cmd(0x2B);
    lcd_set_data(databuf, 4);

    lcd_set_cmd(0x2C); // write to GRAM
}

void lcd_set_cursor(uint16_t xpos, uint16_t ypos)
{
    lcd_set_windows(xpos, ypos, xpos, ypos);
}

void lcd_clear(uint16_t color)
{
    unsigned int i, m;
    uint8_t databuf[2] = {0, 0};
    lcd_set_windows(0, 0, lcd_width - 1, lcd_height - 1);
    for (i = 0; i < lcd_height; i++)
    {
        for (m = 0; m < lcd_width; m++)
        {
            databuf[0] = (color >> 8) & 0xFF;
            databuf[1] = color & 0xFF;
            lcd_set_data(databuf, 2);
        }
    }
}

uint32_t screen_id(void)
{
    lcd_set_cmd(0x04);
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));
    t.length = 8 * 3;
    t.flags = SPI_TRANS_USE_RXDATA;
    t.user = (void *) 1;
    esp_err_t ret = spi_device_polling_transmit(lcd_spi_handle, &t);
    assert(ret == ESP_OK);
    return *(uint32_t *) t.rx_data;
}

void lcd_set_orientation(uint8_t orientation)
{
    uint8_t data[] = {(1 << 3) | (0 << 6) | (0 << 7),            // 0
                      (1 << 3) | (1 << 6) | (1 << 7),            // 1
                      (1 << 3) | (0 << 7) | (1 << 6) | (1 << 5), // 2
                      (1 << 3) | (1 << 7) | (1 << 5)};           // 3

    LCD_Orientation = orientation;
    if (orientation == LCD_DISPLAY_ORIENTATION_PORTRAIT ||
        orientation == LCD_DISPLAY_ORIENTATION_PORTRAIT_INVERTED)
    {
        lcd_width = 240;
        lcd_height = 320;
    }
    else if (orientation == LCD_DISPLAY_ORIENTATION_LANDSCAPE ||
             orientation == LCD_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
    {
        lcd_width = 320;
        lcd_height = 240;
    }

    printf("%s->0x36 command value: 0x%02X\n", "lcd", data[orientation]);
    lcd_set_cmd(0x36);
    lcd_set_data((void *) &data[orientation], 1);
}

bool lcd_init(void)
{
    int cmd = 0;
    lcd_init_cmd_t ili_init_cmds[] = {
        {0xCF, {0x00, 0xD9, 0X30}, 3},
        {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
        {0xE8, {0x85, 0x10, 0x7A}, 3},
        {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
        {0xF7, {0x20}, 1},
        {0xEA, {0x00, 0x00}, 2},
        {0xC0, {0x1B}, 1},       /*Power control*/
        {0xC1, {0x12}, 1},       /*Power control */
        {0xC5, {0x26, 0x26}, 2}, /*VCOM control*/
        {0xC7, {0xB0}, 1},       /*VCOM control*/
        {0x36, {0x08}, 1},       /*Memory Access Control*/
        {0x3A, {0x55}, 1},       /*Pixel Format Set*/
        {0xB1, {0x00, 0x1A}, 2},
        {0xB6, {0x0A, 0xA2}, 2},
        {0xF2, {0x00}, 1},
        {0x26, {0x01}, 1},
        {0xE0,
         {0x1F, 0x24, 0x24, 0x0D, 0x12, 0x09, 0x52, 0XB7, 0x3F, 0x0C, 0x15, 0x06, 0x0E, 0x08, 0x00},
         15},
        {0XE1,
         {0x00, 0x1B, 0x1B, 0x02, 0x0E, 0x06, 0x2E, 0x48, 0x3F, 0x03, 0x0A, 0x09, 0x31, 0x37, 0x1F},
         15},
        {0x2B, {0x00, 0x00, 0x01, 0x3f}, 4},
        {0x2A, {0x00, 0x00, 0x00, 0xEF}, 4},
        {0x11, {0}, 0x80},
        {0x29, {0}, 0x80},
        {0, {0}, 0xff},
    };

    spi_bus_config_t buscfg = {.miso_io_num = PIN_NUM_MISO,
                               .mosi_io_num = PIN_NUM_MOSI,
                               .sclk_io_num = PIN_NUM_CLK,
                               .quadwp_io_num = -1,
                               .quadhd_io_num = -1,
                               .max_transfer_sz = PARALLEL_LINES * 320 * 2 + 8};

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz = 30 * 1000 * 1000,      // clock 30 MHz
        .mode = 0,                               // mode 0
        .spics_io_num = PIN_NUM_CS,              // chip select pin
        .queue_size = 7,                         // transaction queue size
        .pre_cb = lcd_spi_pre_transfer_callback, //
    };

    esp_err_t ret;
    ret = spi_bus_initialize(LCD_HOST, &buscfg, DMA_CHAN);
    ESP_ERROR_CHECK(ret);

    ret = spi_bus_add_device(LCD_HOST, &devcfg, &lcd_spi_handle);
    ESP_ERROR_CHECK(ret);

    gpio_set_direction(PIN_NUM_DC, GPIO_MODE_OUTPUT);
    gpio_set_direction(PIN_NUM_BCKL, GPIO_MODE_OUTPUT);

    gpio_set_level(PIN_NUM_BCKL, 1);

    if (screen_id() <= 0)
        return false;

    while (ili_init_cmds[cmd].databytes != 0xff)
    {
        lcd_set_cmd(ili_init_cmds[cmd].cmd);
        lcd_set_data(ili_init_cmds[cmd].data, ili_init_cmds[cmd].databytes & 0x1F);
        if (ili_init_cmds[cmd].databytes & 0x80)
        {
            vTaskDelay(pdMS_TO_TICKS(100));
        }
        cmd++;
    }

    lcd_set_orientation(LCD_DISPLAY_ORIENTATION_PORTRAIT);
    lcd_set_cmd(0x21); // invert color
    lcd_clear(BLACK);
    return true;
}
