#include <drivers/screen.h>
#include <lib/ui.h>

void status_bar(String title)
{
    screen.setTextSize(2);
    screen.setTextColor(TFT_WHITE);

    int16_t h_font = screen.fontHeight(1);

    screen.fillRect(0, 0, SCREEN_WIDTH, h_font, TFT_DARKGREY1);
    if (title != "")
        screen.drawString(title, 1, 1);

    screen.fillRect(SCREEN_WIDTH - (SCREEN_WIDTH / BACK_BUTTON_SIZE), 0,
                    SCREEN_WIDTH / BACK_BUTTON_SIZE, h_font, TFT_GREY2);

    screen.drawString(
        "x", SCREEN_WIDTH - (SCREEN_WIDTH / BACK_BUTTON_SIZE) + screen.textWidth("x") + 3, 0);
}

void bottom_bar()
{
    screen.setTextSize(1);
    screen.setTextColor(TFT_WHITE);

    // cords based on font size
    int16_t h_font = screen.fontHeight(1);
    int16_t y = SCREEN_HEIGHT - h_font;

    screen.fillRect(0, y, SCREEN_WIDTH, y - 1, TFT_DARKGREY1);

    // Draw RAM
    char buf[32];
    sprintf(buf, "RAM: %dkb", (xPortGetFreeHeapSize() / 1024));
    screen.drawString(buf, SCREEN_WIDTH - screen.textWidth(buf), y);

    // Draw Version
    screen.drawString(FIRMWARE_VERSION, 0, y);
}
