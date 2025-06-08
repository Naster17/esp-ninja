#include "driver/uart.h"
#include "drivers/lcd/cyd28.h"
#include "lib/ui/ui.h"
#include <stdio.h>

void app_main(void)
{
    uart_set_baudrate(UART_NUM_0, 115200); // Set to your desired baud rate
    lcd_init();
    ui_draw_point(10, 10, RED);

    printf("Hell world!\n");

    fflush(stdout);
}
