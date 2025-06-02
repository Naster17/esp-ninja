#include <kernel/package.h>

void app_add_flashlight();
void app_add_grid_demo();
void app_add_scan_wifi();
void app_add_main_toolkit_wifi();
void app_add_wifi_deauth();
void app_add_wifi_locator();
void app_add_wifi_wps();

bool apps_user()
{
    app_add_grid_demo();
    app_add_flashlight();
    app_add_scan_wifi();
    app_add_main_toolkit_wifi();
    app_add_wifi_deauth();
    app_add_wifi_locator();
    app_add_wifi_wps();

    return true;
}
