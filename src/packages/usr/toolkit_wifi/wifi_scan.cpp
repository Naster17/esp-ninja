#include <WiFi.h>
#include <drivers/screen.h>
#include <drivers/wlan.h>
#include <esp_wifi.h>
#include <kernel/package.h>
#include <lib/ui.h>

void selected_wifi(int i);
String get_encription(int i);
String get_cipher(int i, bool group);

void app_wifi_scan(void *lp_param)
{
    // wifi_init_config_t config = WIFI_INIT_CONFIG_DEFAULT();
    // esp_wifi_init(&config);
    // esp_wifi_set_channel(11, WIFI_SECOND_CHAN_NONE);

    screen.fillScreen(TFT_BLACK);
    status_bar("Scanning...");
    bottom_bar();

    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    int n = WiFi.scanNetworks(false, true, false);

    GridView *aps;
    uint8_t text_size = 2;
    if (n == 0)
    {
        aps = grid_init(8, 1);
        constructor(aps, "No APs found!", TILE_BUTTON, 2);
    }
    else if (n > 14)
    {
        text_size = 1;
        aps = grid_init(14, 1);
    }
    else
    {
        aps = grid_init(n, 1);
    }

    for (int i = 0; i < n; ++i)
    {
        String title = WiFi.SSID(i) != "" ? WiFi.SSID(i) : WiFi.BSSIDstr(i);
        constructor(aps, title, TILE_BUTTON, text_size);
    }

    unsigned long t = 0;
    while (1)
    {
        String msg = handler(aps);
        if (msg == "EXIT")
            break;

        if (msg != "")
        {
            for (int i = 0; i < n; ++i)
            {
                if (msg == WiFi.SSID(i) || msg == WiFi.BSSIDstr(i))
                {
                    selected_wifi(i);
                    grid_refresh(aps);
                }
            }
        }

        if (millis() - t > 5000)
        {
            bottom_bar();
            status_bar("APs");
            t = millis();
        }
        delay(50);
    }
    WiFi.scanDelete();
    WiFi.disconnect(true, true);
    WiFi.mode(WIFI_OFF);

    grid_deinit(aps);
}

void selected_wifi(int i)
{
    int c = i;
    // if wifi id out of scope
    if (WiFi.BSSIDstr(i) == 0)
        return;

    screen.fillScreen(TFT_BLACK);
    status_bar(WiFi.SSID(i));
    bottom_bar();

    GridView *grid1 = grid_init(6, 2);
    constructor(grid1, "Previous", TILE_BUTTON, 2);
    constructor(grid1, "Second", TILE_BUTTON, 2);

    GridView *grid2 = grid_poly_init(grid1, 8, 1);
    constructor(grid2, "Select", TILE_BUTTON, 2);

    GridView *grid3 = grid_poly_init(grid2, 1, 1);

    wifi_ap_record_t *it = (wifi_ap_record_t *) WiFi.getScanInfoByIndex(i);
    String output = "SSID:  " + (WiFi.SSID(i) != "" ? WiFi.SSID(i) : "HIDDEN") + "\n\n" +
                    "BSSID: " + WiFi.BSSIDstr(i) + "\n" + "RSSI:  " + String(WiFi.RSSI(i)) +
                    "dbm\n" + "WPS:   " + (it->wps ? "ON" : "OFF") + "\n\n" +
                    "Channel:  " + String(WiFi.channel(i)) + "\n" +
                    "Security: " + get_encription(i) + "\n" + "Cipher:   " + get_cipher(i, false) +
                    "/" + get_cipher(i, true) + "\n\n" + "Mode: " + "802.11" +
                    (it->phy_11b ? "b" : "") + (it->phy_11g ? "g" : "") + (it->phy_11n ? "n" : "") +
                    "\n" + "Low Rate: " + (it->phy_lr ? "ON" : "OFF") + "\n" +
                    "FTM Init: " + (it->ftm_initiator ? "YES" : "NO") + "\n" +
                    "FTM Resp: " + (it->ftm_responder ? "YES" : "NO") + "\n\n" +
                    "Antenna:  " + (it->ant == 1 ? "1" : "0") + "\n";

    grid_add_output(grid3, output, TEXT_POSITION_TOP_LEFT, 1);

    unsigned long bar_t = 0;
    while (1)
    {
        String ps = handler(grid1);
        String attack = handler(grid2);

        if (ps == "EXIT")
        {
            break;
        }
        else if (ps == "Second")
        {
            c += 1;
            delay(50);
            break;
        }
        else if (ps == "Previous")
        {
            c -= 1;
            delay(50);
            break;
        }
        else if (attack == "Select")
        {
            // Simple executor
            for (int i = 1; i < apps->count + 1; i++)
            {
                if (apps->list[i].app_name == "SelectWifi")
                {
                    apps->list[i].entry(&c);
                    break;
                }
            }
            break;
        }
        delay(50);
    }
    grid_deinit(grid1);
    grid_deinit(grid2);
    grid_deinit(grid3);

    if (c != i)
        selected_wifi(c);
}

String get_encription(int i)
{
    int e = WiFi.encryptionType(i);
    switch (e)
    {
    case WIFI_AUTH_OPEN: return "OPEN";
    case WIFI_AUTH_WEP: return "WEP";
    case WIFI_AUTH_WPA_PSK: return "WPA_PSK";
    case WIFI_AUTH_WPA2_PSK: return "WPA2_PSK";
    case WIFI_AUTH_WPA_WPA2_PSK: return "WPA_WPA2_PSK";
    case WIFI_AUTH_ENTERPRISE: return "ENTERPRISE";
    case WIFI_AUTH_WPA3_PSK: return "WPA3_PSK";
    case WIFI_AUTH_WPA2_WPA3_PSK: return "WPA2_WPA3_PSK";
    case WIFI_AUTH_WAPI_PSK: return "WAPI_PSK";
    case WIFI_AUTH_WPA3_ENT_192: return "WPA3_ENT_192";
    default: return "UNKNOWN";
    }
}

String get_cipher(int i, bool group)
{
    wifi_ap_record_t *it = reinterpret_cast<wifi_ap_record_t *>(WiFi.getScanInfoByIndex(i));
    int cipher;
    if (group)
        cipher = it->group_cipher;
    else
        cipher = it->pairwise_cipher;

    switch (cipher)
    {
    case WIFI_CIPHER_TYPE_NONE: return "NONE";
    case WIFI_CIPHER_TYPE_WEP40: return "WEP40";
    case WIFI_CIPHER_TYPE_WEP104: return "WEP140";
    case WIFI_CIPHER_TYPE_TKIP: return "TKIP";
    case WIFI_CIPHER_TYPE_CCMP: return "CCMP";
    case WIFI_CIPHER_TYPE_TKIP_CCMP: return "TKIP_CCMP";
    case WIFI_CIPHER_TYPE_AES_CMAC128: return "AES_CMAC128";
    case WIFI_CIPHER_TYPE_SMS4: return "SMS4";
    case WIFI_CIPHER_TYPE_GCMP: return "GCMP";
    case WIFI_CIPHER_TYPE_GCMP256: return "GCMP256";
    case WIFI_CIPHER_TYPE_AES_GMAC128: return "AES_GMAC128";
    case WIFI_CIPHER_TYPE_AES_GMAC256: return "AES_GMAC256";
    default: return "UNKNOWN";
    }
}

void app_add_scan_wifi()
{
    app_add("Scan", "Wifi", app_wifi_scan);
}
