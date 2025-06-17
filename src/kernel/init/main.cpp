#include <Arduino.h>
#include <drivers/screen.h>

void boot();

void setup()
{
    Serial.begin(115200);
    screen_rotate(0);
    boot();
}

void loop() {}
