#include <Arduino.h>
#include <drivers/screen.h>
#include <kernel/packages.h>
#include <lib/ui.h>
/*
 * If you are surprised by this code and are not very familiar with the C language
 * and its philosophy, cus this is an intermediate layer between simplicity and community
 * support, and low-level code on C
 * All the complications in the form of my wrappers around the functions of libraries and
 * the Arduino framework are not accidental, but created specifically for the
 * future migration to the C language. By big fat ass C++
 */

void boot();

int prt(void *p)
{
    Serial.println("Fuck");
    return 0;
}

void setup()
{
    screen_rotate(0);
    boot();

    screen_printf("wewe %s dick %d\n", "cock", 32);
    screen_clear();

    navbar();
    statusbar();

    pkg_add("Wewe", "boy", prt);
    pkg_add("Wewe2", "boy2", prt);
    pkg_add("Wewe3", "boy3", prt);
    pkg_debug();
}

void loop() {}
