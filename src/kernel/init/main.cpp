#include <Arduino.h>
#include <drivers/screen.h>
#include <kernel/packages.h>

void boot();

int prt(void *p)
{
    Serial.println("Fuck");
    return 0;
}

void setup()
{
    Serial.begin(115200);
    screen_rotate(0);
    boot();
    screen_printf("wewe %s dick %d\n", "cock", 32);

    pkg_add("Wewe", "boy", prt);
    pkg_add("Wewe2", "boy2", prt);
    pkg_add("Wewe3", "boy3", prt);
    pkg_debug();
}

void loop() {}
