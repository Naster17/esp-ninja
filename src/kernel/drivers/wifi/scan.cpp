#include "WiFi.h"
#include "wifi_hal.h"


String scan_aps()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);

    const int n = WiFi.scanNetworks();
    String arr[n][3];
    
    for (int i = 0; i < n; ++i)
    {
        arr[i][0] = WiFi.SSID(i);
        arr[i][1] = WiFi.RSSI(i);
        arr[i][2] = WiFi.encryptionType(i);
    }

    return "";
}