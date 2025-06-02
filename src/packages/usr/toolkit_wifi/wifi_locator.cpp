#include <WiFi.h>
#include <esp_wifi.h>
#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

void app_wifi_locator(void *lp_param)
{
    int c = *(int *)lp_param;

    screen.fillScreen(TFT_BLACK);
    status_bar(WiFi.SSID(c) != "" ? WiFi.SSID(c) : WiFi.BSSIDstr(c));
    bottom_bar();

    GridView *dbm = grid_init(6, 1);

    int dbm_id = grid_add_output(dbm, String(WiFi.RSSI(c)) + "dbm", TEXT_POSITION_CENTER, 2);

    GridView *btn = grid_poly_init(dbm, 2, 1);
    grid_add_button(btn, "SCAN", 2);
    grid_add_button(btn, "AUTO SCAN", 2);

    bool auto_scan = false;
    unsigned long tmp = 0;
    while (1)
    {
        String m_btn = handler(btn);
        if (m_btn == "EXIT")
            break;

        if (m_btn == "SCAN")
        {
            WiFi.scanNetworks(false, true, false, 300U, WiFi.channel(c), nullptr, WiFi.BSSID(c));
            grid_output_write(dbm, dbm_id, String(WiFi.RSSI(c)) + "dbm", TEXT_POSITION_CENTER, 2, false);
        }
        else if (m_btn == "AUTO SCAN")
            auto_scan = !auto_scan;

        if (auto_scan && millis() - tmp > 500)
        {
            if (WiFi.RSSI(c) != 0)
                grid_output_write(dbm, dbm_id, String(WiFi.RSSI(c)) + "dbm", TEXT_POSITION_CENTER, 2, false);

            WiFi.scanNetworks(true, true, false, 300U, WiFi.channel(c), nullptr, WiFi.BSSID(c));
            tmp = millis();
        }
    }

    grid_deinit(dbm);
    grid_deinit(btn);
}

void app_add_wifi_locator()
{
    app_add("Locator", "ToolkitWiFi", app_wifi_locator);
}
