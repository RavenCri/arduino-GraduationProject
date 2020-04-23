#ifndef WIFI_H
#define WIFI_H
#include <WiFi.h>
#include <WiFiSTA.h>
extern boolean connectFlag;
class WifiService{
  public:
    void setup_wifi();
    void createWiFiAP();
};
#endif
