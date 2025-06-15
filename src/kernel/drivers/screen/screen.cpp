#include <drivers/screen.h>

TFT_eSPI screen = TFT_eSPI();
uint8_t SCREEN_ROTATE = 0;          // rotate pos
int32_t SCREEN_HEIGHT = TFT_HEIGHT; // dymanic HEIGHT
int32_t SCREEN_WIDTH = TFT_WIDTH;   // dymanic WIDTH


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
