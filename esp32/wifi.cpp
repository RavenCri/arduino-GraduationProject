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
    common.s_print("WIFI连接失败，请重新配置您的信息");
    delay(500);
    char wifi_id[100];
    sprintf(wifi_id,"热点名称：%s",(const char*)device_jSON["mySsid"]);
    //common.s_print((const char*)device_jSON["mySsid"]);
    delay(200);
    common.s_print(wifi_id);
    char password[100];
    sprintf(password,"热点密码：%s",(const char*)device_jSON["myPassword"]);
    delay(200);
    common.s_print(password);
    Serial.println("WiFi Create Success!");
    delay(200);
    common.s_print("设备IP："+common.getIP(WiFi.softAPIP()));
}
