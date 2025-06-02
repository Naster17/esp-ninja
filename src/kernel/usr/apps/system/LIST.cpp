#include "../apps.h"

void app_add_flashlight();
void app_add_main();
void app_add_apps();
void app_add_debug();
void app_add_bluetooth();
void app_add_wifi();
void app_add_options();

bool apps_system()
{
    app_add_main();
    app_add_bluetooth();
    app_add_apps();
    app_add_debug();
    app_add_wifi();
    app_add_options();

    return true;
}