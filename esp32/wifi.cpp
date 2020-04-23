#include "wifi.h"
#include "common.h"
#include "file.h"
extern JSONVar device_jSON;
boolean connectFlag = true;
void WifiService::setup_wifi() {

  common.s_print("开始连接WIFI ssid："+JSON.stringify(device_jSON["connectSsid"]));
  Serial.println("wifi密码："+JSON.stringify(device_jSON["connectPassword"]));
  //连接用户wifi
  WiFi.begin(device_jSON["connectSsid"],device_jSON["connectPassword"] );
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    unsigned long endTime = millis();
    // 如果10s还没连上 跳出循环
    if(endTime - startTime >=10000){
      connectFlag = false;
      break;
    }
  }
  // 如果没有连接上WIFI
  if(!connectFlag){
      this->createWiFiAP();
  }else{ 
      randomSeed(micros());
      common.s_print("WiFi connected Success!");
      common.s_print("设备IP： "+common.getIP(WiFi.localIP()));
      Serial.println("云服务器地址："+JSON.stringify(device_jSON["publicAddress"]));
  }
}

void WifiService::createWiFiAP(){
    WiFi.mode(WIFI_AP);
    WiFi.softAP(device_jSON["mySsid"],device_jSON["myPassword"]);
    common.s_print("WIFI连接失败，请连接该设备热点重新配置您的信息。正在创建热点...");
    delay(200);
    common.s_print("热点名称：");
    delay(200);
    common.s_print((const char*)device_jSON["mySsid"]);
    common.s_print("热点密码：");
    delay(200);
    Serial.println((const char*)device_jSON["myPassword"]);
    Serial.println("WiFi Create Success!");
    common.s_print("设备IP："+common.getIP(WiFi.softAPIP()));
}
