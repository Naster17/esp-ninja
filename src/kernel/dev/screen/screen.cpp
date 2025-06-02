#include "screen.h"
// tft

TFT_eSPI screen = TFT_eSPI();
uint8_t SCREEN_ROTATE = 0;          // rotate pos
int32_t SCREEN_HEIGHT = TFT_HEIGHT; // dymanic HEIGHT
int32_t SCREEN_WIDTH = TFT_WIDTH;   // dymanic WIDTH

#ifdef ILI9341_2_DRIVER
CYD28_TouchR touch(TFT_HEIGHT, TFT_WIDTH);
#endif

bool screen_init()
{
    screen.init();
    screen.invertDisplay(1);
    screen.setRotation(SCREEN_ROTATE);
    screen.fillScreen(TFT_BLACK);

    pinMode(TFT_BL, OUTPUT);
    ledcSetup(0, 5000, 8); // Channel 0, 10khz, 8bits
    ledcAttachPin(TFT_BL, 0);
    ledcWrite(0, 255);
    return true;
}

// touch
bool touch_init()
{
    pinMode(TOUCH_CS, OUTPUT);
    digitalWrite(TOUCH_CS, HIGH);

    if (!touch.begin())
    {
        return false;
    }
    else
    {
        return true;
        touch.setRotation(SCREEN_ROTATE);
        touch.setThreshold(50);
    }
}

void set_rotate(int r)
{

    if (r == 0)
    {
        SCREEN_WIDTH = TFT_WIDTH;
        SCREEN_HEIGHT = TFT_HEIGHT;
    }
    if (r == 1)
    {
        SCREEN_WIDTH = TFT_HEIGHT;
        SCREEN_HEIGHT = TFT_WIDTH;
    }
    if (r == 2)
    {
        SCREEN_WIDTH = TFT_WIDTH;
        SCREEN_HEIGHT = TFT_HEIGHT;
    }
    if (r == 3)
    {
        SCREEN_WIDTH = TFT_HEIGHT;
        SCREEN_HEIGHT = TFT_WIDTH;
    }

    SCREEN_ROTATE = r;
    screen.setRotation(r);
    touch.setRotation(r);

    screen.fillScreen(TFT_BLACK);
}