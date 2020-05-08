#include "mqtt.h"


WiFiClient espClient;
PubSubClient mqttClient(espClient);
HttpService httpService;

void MqttService::connectServer(){
  
  mqttClient.setServer(device_jSON["publicAddress"], 1883);
  mqttClient.setCallback(callback);
   // 如果wifi连接成功且mqtt未连接
  if (connectFlag && !mqttClient.connected()) {
    Serial.println("开始请求mqtt信息...");
    String username = JSON.stringify(device_jSON["username"]);
    String password = JSON.stringify(device_jSON["password"]);
    String postData = "username="+username+"&password="+password;
    
    String response = httpService.postRequest("/mqtt/getMqttInfo",postData);
    String mqttUsername;
    String mqttPassword;

    // 创建一个随机id
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if(response != "error"){
       JSONVar req =  JSON.parse(response);
       mqttUsername = req["data"]["mqttUsername"];
       mqttPassword = req["data"]["mqttPassword"];
       if(((int)req["code"]) == 200){
         Serial.print("请求到的mqtt账号：");
         Serial.println(mqttUsername);
         Serial.print("请求到的mqtt密码：");
         Serial.println(mqttPassword);
       }else{
         common.s_print("请求mqtt连接失败，请重新配置用户账号密码");
         return;
       }  
    }else{
      common.s_print("服务器请求异常，请检查路由器是否可以正常上网");
      return;
    }
    Serial.println("开始连接mqtt服务器...");
    // 开始连接mqtt服务器
    if (mqttClient.connect(clientId.c_str(),mqttUsername.c_str(),mqttPassword.c_str())) {
      common.s_print("mqtt服务器连接成功!");
      delay(200);
      //订阅消息
      String subscribe = JSON.stringify(device_jSON["deviceId"])+"-"+JSON.stringify(device_jSON["deviceKey"]);
      // 从json获取的属性带引号应该去掉！
      subscribe.replace("\"","");  
      mqttClient.subscribe(subscribe.c_str());
      Serial.println("已成功订阅节点消息:{"+subscribe+"}");
    } else {
      common.s_print("mqtt服务器连接失败");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String data = "";
  for (int i = 0; i < length; i++) {    
    data += (char)payload[i];
  }
  common.s_print(data);
}
