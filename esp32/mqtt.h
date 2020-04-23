#pragma once
#include "common.h"
#include "wifi.h"
#include "http.h"

//MQTT 库
#include <PubSubClient.h>
void callback(char* topic, byte* payload, unsigned int length);
extern JSONVar device_jSON;
extern HttpService httpService;
extern Common common;
class MqttService{
  public:
   
    void connectServer();
};
