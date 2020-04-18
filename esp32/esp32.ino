//ArduinoJSON库
#include <Arduino_JSON.h>
#include <WiFi.h>
//MQTT 库
#include <PubSubClient.h>
#include <WiFiSTA.h>
// 文件操作库
#include "SPIFFS.h"
#include "FS.h"
//ESP Async WebServer库
#include <Arduino.h>
#ifdef ESP32
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);
//ArduinoHttpClient库
#include <ArduinoHttpClient.h>

//后台服务器的端口
int port = 8080;

const int mqttPort = 1883;
boolean connectFlag = true;

#define arduinoSerial Serial2
WiFiClient espClient;
PubSubClient mqttClient(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
JSONVar device_jSON;
WiFiClient wifi;

void setup() {
  Serial.begin(115200);
  //读取配置文件
  init(SPIFFS);
  //连接WIFI
  setup_wifi();
  //启动web服务器
  startWebServer();
}
void loop() {
  // 若未连接上，则一直连接WIFI
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
  unsigned long now = millis();
  Serial.println(now);
  if (now - lastMsg > 10000) {
    lastMsg = now;
    HttpClient httpClient = HttpClient(wifi, device_jSON["publicAddress"], port);
    String deviceId = JSON.stringify(device_jSON["deviceId"]);
    deviceId.replace("\"","");
    httpClient.get("/device/keepOnline?deviceId="+deviceId);
    Serial.println("发送心跳包...");
    //snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    //client.publish("outTopic", msg);
  }
  delay(1000);
}
void s_print(String str){
  str.replace("\"","");
  Serial.println(str);
  arduinoSerial.print(str);
}
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
void setup_wifi() {
  delay(10);
  arduinoSerial.begin(9600);
  s_print("开始连接 WIFI ssid：");
  s_print(JSON.stringify(device_jSON["connectSsid"]));
  s_print("wifi密码：");
  s_print(JSON.stringify(device_jSON["connectPassword"]));
  //连接用户wifi
  WiFi.begin(device_jSON["connectSsid"],(const char*)device_jSON["connectPassword"] );
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
    WiFi.mode(WIFI_AP);
    WiFi.softAP(device_jSON["mySsid"],device_jSON["myPassword"]);
    s_print("WIFI连接失败，请连接该设备热点重新配置您的信息。正在创建热点...");
    s_print("热点名称：");
    s_print((const char*)device_jSON["mySsid"]);
    s_print("热点密码：");
    Serial.println((const char*)device_jSON["myPassword"]);
    Serial.println("WiFi Create Success!");
    s_print("IP address: ");
    s_print(getIP(WiFi.softAPIP()));
  }else{ 
    randomSeed(micros());
    Serial.println("");
    s_print("WiFi connected Success!");
    s_print("IP address: ");
    s_print(getIP(WiFi.localIP()));
    Serial.println("云服务器地址：");
    Serial.println(JSON.stringify(device_jSON["publicAddress"]));
    mqttClient.setServer(device_jSON["publicAddress"], mqttPort);
    mqttClient.setCallback(callback);
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
  s_print(data);
}

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    
    Serial.printf("Listing directory: %s\r\n", dirname);
    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return;
    }
    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}


void reconnect() {
  // 如果wifi连接成功
  while (connectFlag && !mqttClient.connected()) {
    HttpClient httpClient = HttpClient(wifi, device_jSON["publicAddress"], port);
    String contentType = "application/x-www-form-urlencoded";
    String username = JSON.stringify(device_jSON["username"]);
    String password = JSON.stringify(device_jSON["password"]);
    String postData = "username="+username+"&password="+password;
    httpClient.post("/mqtt/getMqttInfo", contentType, postData);
    int statusCode = httpClient.responseStatusCode();
    String response = httpClient.responseBody();
    String mqttUsername;
    String mqttPassword;
    s_print("开始请求MQTT信息...");
    // 创建一个随机id
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if(statusCode == 200){
       JSONVar req =  JSON.parse(response);
       Serial.println(JSON.stringify(req));
       mqttUsername = req["data"]["mqttUsername"];
       mqttPassword = req["data"]["mqttPassword"];
       if(((int)req["code"]) == 200){
         Serial.print("请求到的mqtt账号：");
         Serial.println(mqttUsername);
         Serial.print("请求到的mqtt密码：");
         Serial.println(mqttPassword);
       }else{
         s_print("请求MQTT连接失败，请重新配置用户账号密码");
         return;
       }  
    }else{
      s_print("服务器请求异常，请检查路由器是否可以正常上网");
      return;
    }
    Serial.println("开始连接MQTT服务器...");
    // 开始连接mqtt服务器
    if (mqttClient.connect(clientId.c_str(),mqttUsername.c_str(),mqttPassword.c_str())) {
      s_print("MQTT服务器连接成功!");
      //订阅消息
      String subscribe = JSON.stringify(device_jSON["deviceId"])+"-"+JSON.stringify(device_jSON["deviceKey"]);
      // 从json获取的属性带引号应该去掉！
      subscribe.replace("\"","");  
      mqttClient.subscribe(subscribe.c_str());
      Serial.println("已成功订阅节点消息:{"+subscribe+"}");
    } else {
      s_print("MQTT服务器连接失败, rc=");
      Serial.println(""+mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void init(fs::FS &fs){
  Serial.println("文件列表：");
  listDir(SPIFFS, "/", 0);
  if(!SPIFFS.begin(true)){
     Serial.println("安装SPIFFS时发生错误...");
     return;
  }
  Serial.println("读取配置文件中...");
  File device_file = fs.open("/data.json",FILE_READ);
  if(!device_file || device_file.size()==0){
    s_print("配置文件不存在，即将创建配置文件...");  
    device_file.close();
    device_file = fs.open("/data.json", FILE_WRITE);
    if(!device_file){
        s_print("创建配置文件失败！");
        return;
    }
    JSONVar deviceJSON;
    deviceJSON['deviceId']="";
    deviceJSON['devicePassword']="";
    deviceJSON['version']="1.0.0";
    deviceJSON['connectSsid']="";
    deviceJSON['connectPassword']="";
    deviceJSON['mySsid']="";
    deviceJSON['myPassword']="";
    deviceJSON['username']="";
    deviceJSON['password']="";
    if(device_file.print(JSON.parse(deviceJSON))){
        Serial.println("配置文件写入创建...");
    } else {
        Serial.println("配置文件写入失败...");
    }
    device_file.close();
    //应该重新读取
    device_file = fs.open("/data.json");
  }
  Serial.println("文件内容:");
  String driver = "";
  while(device_file.available()){  
      driver += (char)device_file.read();
  }
  device_file.close();
  Serial.println(driver);
  device_jSON = JSON.parse(driver);
}

//启动web服务器
void startWebServer(){
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.on("/update", HTTP_POST, [] (AsyncWebServerRequest *request) {
        int params = request->params();
        for(int i = 0;i < params;i++){
           device_jSON[request->getParam(i)->name().c_str()] = request->getParam(i)->value();
        }
        Serial.println(device_jSON);
        //保存用户提交的数据
        boolean flag = writeFile(SPIFFS,"/data.json",JSON.stringify(device_jSON));
        if(flag){
          request->send(200, "text/plain", "ok");
        }else{
          request->send(200, "text/plain", "error");
        }
   });
   server.onNotFound(notFound);
   server.begin();
   s_print("web服务已启动！");
}


// 写入文件
boolean writeFile(fs::FS &fs, const char * path, String message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return false;
    }
    if(file.print(message)){
        Serial.println("- file written");
        return true;
    } else {
        Serial.println("- frite failed");
        return false;
    }
}

  
String getIP(IPAddress ip)//获取UDP 广播地址
{
    
  int buf[4];
 
  for (int i = 0; i < 4; i++)
  {
    buf[i] = ip[i];
  }
  String temp = "";
  temp += String(ip[0]);
  temp += '.';
  temp += String(ip[1]);
  temp += '.';
  temp += String(ip[2]);
  temp += '.';
  temp += String(ip[3]);
  return temp;
}
