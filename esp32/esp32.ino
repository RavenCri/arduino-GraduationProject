#include "common.h"
#include "file.h"
#include "http.h"
#include "Arduino.h"
#include "mqtt.h"
#include "wifi.h"
//#include "Queue.h"
WifiService wifiService;
MqttService mqttService;
extern HttpService httpService;
extern FileService fileService;
const int port = 8080;//后台服务器的端口
int lastMills = 0;
//DataQueue<String> intQueue(10);
extern PubSubClient mqttClient;
extern boolean connectFlag;
void setup() {
  Serial.begin(115200);
  arduinoSerial.begin(4800);
  //读取配置文件
  fileService.init();
  //初始化WIFI
  wifiService.setup_wifi();
  //启动web服务器
  httpService.startWebServer();
}
void loop() {
  // 检测是否连接上MQTT服务器
  if (!mqttClient.connected()) {
    mqttService.connectServer();
  }
  mqttClient.loop();
  unsigned long now = millis();
  if (connectFlag ) {
    if(now - lastMills > 10000){
      lastMills = now;
      httpService.heartPackage();
    }
    onTimer();
  }
  
  delay(200);
}



void onTimer()
{
    String str ="";
    if( arduinoSerial.available()>0 ){
      delay(20);
      char c;
      while( arduinoSerial.available()>0  ){
         c = arduinoSerial.read();
         str += c;  
      }
      if(  ((int)str.charAt(0)) == -1 || ((int)str.charAt(0) ) == 0 )return;
      Serial.println("收到Arduino："+str);
      //intQueue.enqueue(data);
      JSONVar sendData =  JSON.parse(str);
      sendData["username"] = (const char *)device_jSON["username"];
      sendData["deviceKey"] = (const char *)device_jSON["deviceKey"];
      sendData["deviceId"] = (const char *)device_jSON["deviceId"];
      String postData = common.getPostData(sendData);
      Serial.println(postData);
      String response = httpService.postRequest("/push_msg/user",postData);
      if(response != "error"){
        Serial.println("发布成功");
      }else{
        Serial.println("发布失败");
      }
      //mqttClient.publish(to.c_str(),(const char*)json["msg"]);
   }
}
