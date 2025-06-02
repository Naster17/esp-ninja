#include <WiFi.h>
#include <esp_wps.h>
#include <esp_wifi.h>
#include "kernel/usr/gui/gui.h"
#include "kernel/usr/apps/apps.h"
#include "kernel/dev/screen/screen.h"

void WiFiEvent(WiFiEvent_t event, arduino_event_info_t info);
void wpsStart();
void wpsStop();

String last_log;

void app_wifi_wps(void *lp_param)
{
    last_log = "";

    screen.fillScreen(TFT_BLACK);
    status_bar("WPS Button");
    bottom_bar();

    delay(10);
    Serial.println();
    WiFi.onEvent(WiFiEvent); // Will call WiFiEvent() from another thread.
    WiFi.mode(WIFI_MODE_STA);
    last_log += "Starting WPS\n";
    wpsStart();

    GridView *grid = grid_init(1, 1);
    int idd = grid_add_output(grid, "", TEXT_POSITION_TOP_LEFT, 1);

    String old = "";
    while (1)
    {
        String msg = handler(grid);
        if (msg == "EXIT")
            break;

        if (last_log != old)
        {
            grid_output_write(grid, idd, last_log, TEXT_POSITION_TOP_LEFT, 1, false);
            old = last_log;
        }
    }

    grid_deinit(grid);
    wpsStop();
    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);
}

void wpsStart()
{
    esp_wps_config_t config;
    memset(&config, 0, sizeof(esp_wps_config_t));

    config.wps_type = WPS_TYPE_PBC;
    strcpy(config.factory_info.manufacturer, "ESPRESSIF");
    strcpy(config.factory_info.model_number, CONFIG_IDF_TARGET);
    strcpy(config.factory_info.model_name, "ESPRESSIF IOT");
    strcpy(config.factory_info.device_name, "ESP DEVICE");

    esp_err_t err = esp_wifi_wps_enable(&config);
    if (err != ESP_OK)
    {
        last_log += "WPS Enable Failed!\n";
        return;
    }

    err = esp_wifi_wps_start(0);
    if (err != ESP_OK)
    {
        last_log += "WPS Start Failed!\n";
    }
}

void wpsStop()
{
    esp_err_t err = esp_wifi_wps_disable();
    if (err != ESP_OK)
    {
        last_log += "WPS Disable Failed!\n";
    }
}

// WARNING: WiFiEvent is called from a separate FreeRTOS task (thread)!
void WiFiEvent(WiFiEvent_t event, arduino_event_info_t info)
{
    switch (event)
    {
    case ARDUINO_EVENT_WIFI_STA_START:
        break;
    case ARDUINO_EVENT_WIFI_STA_GOT_IP:
        last_log += "\nCaptured:\n" + String(WiFi.SSID()) + "\n" + String(WiFi.psk()) + "\n";
        wpsStop();
        WiFi.disconnect(true, true);
        WiFi.mode(WIFI_OFF);
        break;
    case ARDUINO_EVENT_WIFI_STA_DISCONNECTED:
        break;
    case ARDUINO_EVENT_WPS_ER_SUCCESS:
        last_log += "\nCaptured:\n" + String(WiFi.SSID()) + "\n" + String(WiFi.psk()) + "\n";
        wpsStop();
        WiFi.disconnect(true, true);
        WiFi.mode(WIFI_OFF);
        break;
    case ARDUINO_EVENT_WPS_ER_FAILED:
        last_log += "WPS Failed, retrying\n";
        wpsStop();
        wpsStart();
        break;
    case ARDUINO_EVENT_WPS_ER_TIMEOUT:
        last_log += "WPS Timedout, retrying\n";
        wpsStop();
        wpsStart();
        break;
    case ARDUINO_EVENT_WPS_ER_PIN:
        break;
    default:
        break;
    }
}

void app_add_wifi_wps()
{
    app_add("WPS Button", "Wifi", app_wifi_wps);
}