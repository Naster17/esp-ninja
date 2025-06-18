#include <Arduino.h>
#include <drivers/led.h>
#include <drivers/screen.h>
#include <drivers/touch.h>
#include <kernel/packages.h>
#include <lib/ui.h>

void boot()
{
    bool boot_failed = false;
    bootlog("Initializing screen...", screen_init());
    bootlog("Initializing touch...", touch_init());
    bootlog("Failed test...", 0);

#ifdef LED_RGB
    bootlog("Initializing RGB LED...", rgb_init());
    bootlog("RGB LED blinking test!", BOOT_LVL_INFO);
    blink(3, 1, 1, 1);
#else
    bootlog("Initializing Generic LED...", led_init());
#endif
    bootlog("Creating GUI structs.....", BOOT_LVL_OK);
    // bootlog("Starting Apps subsystem...", apps_init());
    // bootlog("Load system apps.", apps_system());
    // bootlog("Load user apps.", apps_user());
    // if (apps_loaded() != 0)
    // {
    //     char buff[64];
    //     sprintf(buff, "Loaded: %d apps", apps_loaded());
    //     bootlog(buff, BOOT_LVL_OK);
    // }
    // else
    // {
    //     boot_failed = true;
    //     bootlog("Loaded: 0 apps (Check it)", BOOT_LVL_FAILED);
    // }
    bootlog("FirmwareVersion: " FIRMWARE_VERSION, BOOT_LVL_INFO);
    bootlog("Welcome to ESP32Ninja-NG", BOOT_LVL_INFO);

    if (boot_failed)
    {
        bootlog("Check log", BOOT_LVL_FAILED);
        bootlog("CLICK TO CONTINUE!", BOOT_LVL_FAILED);
    }

    for (uint8_t i = 0; i < 20; i++)
    {
        if (touch_touched())
            i--;
        if (boot_failed)
            i--;

        delay(100);
    }
    // timely dissabled
    // Simple executor
    // for (int i = 1; i < apps->count + 1; i++)
    // {
    //     if (apps->list[i].app_name == "Main")
    //     {
    //         apps->list[i].entry(NULL);
    //         break;
    //     }
    // }
    // // if Main app not found
    // bootlog("Started App NOT FOUND!", BOOT_LVL_FAILED);
}
