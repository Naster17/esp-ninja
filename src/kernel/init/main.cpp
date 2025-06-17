#include <Arduino.h>
#include <drivers/led.h>
#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

void boot();

void setup()
{
    Serial.begin(115200);
    screen_rotate(0);
    boot();

}

void loop() {}
