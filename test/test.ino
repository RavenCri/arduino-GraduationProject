#include <Arduino_JSON.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiSTA.h>
#include "SPIFFS.h"
#include "FS.h"
#include <Arduino.h>
#ifdef ESP32
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;
AsyncWebServer server(80);
const char* ssid = "F";
//const char* password =  "13892393046";
//const char* password =  "11111";
//const char* myssid = "hfuu_raven";
//const char* mypassword = "love12345";
//const char* mqtt_server = "192.168.0.103";
//const char* user = "raven";
//const char* pass = "123456";
const int mqttPort = 1883;
boolean connectFlag = false;

#define arduinoSerial Serial2
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
JSONVar device_jSON;
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
void setup_wifi() {
  delay(10);
  arduinoSerial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.println("开始连接WIFI：%s,密码：%s",device_jSON["ssid"],device_jSON["password"] );
  //连接用户wifi
  WiFi.begin(device_jSON["ssid"],device_jSON["password"] );
  unsigned long startTime = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    unsigned long endTime = millis();
    // 如果10s还没连上 跳出循环
    if(endTime - startTime >=10000){
      connectFlag = true;
      espClient.stop();
      break;
    }
  }
  // 如果没有连接上WIFI
  if(connectFlag){
    WiFi.mode(WIFI_AP);
    WiFi.softAP(device_jSON["myssid"],device_jSON["mypassword"]);
    Serial.println("WIFI连接失败，请连接该设备热点重新配置您的信息。正在创建热点...");
    Serial.println("热点名称：%s,热点密码：%s",device_jSON["myssid"],device_jSON["mypassword"]);
    Serial.println("WiFi Create Success!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }else{
    randomSeed(micros());
    Serial.println("");
    Serial.println("WiFi connected Success!");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    client.setServer(mqtt_server, mqttPort);
    client.setCallback(callback);
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
  Serial.println(data);
  arduinoSerial.print(data);
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
  while (connectFlag && !client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // 创建一个随机id
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // 开始连接mqtt服务器
    if (client.connect(clientId.c_str(),user,pass)) {
      Serial.println("connected");
      // 发布消息
      client.publish("outTopic", "hello world");
      //订阅消息
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void init(fs::FS &fs){
  Serial.println("文件列表：");
  listDir(SPIFFS, "/", 0);
  Serial.println("读取配置文件中...");
  if(!SPIFFS.begin(true)){
     Serial.println("安装SPIFFS时发生错误...");
     return;
  }
  File device_file = fs.open("/data.json");
  if(!device_file || device_file.size()==0){
    Serial.println("配置文件不存在，即将创建配置文件...");
    device_file.close();
    device_file = fs.open("/data.json", FILE_WRITE);
    if(!device_file){
        Serial.println("创建配置文件失败！");
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
   Serial.println("web服务已启动！");
}
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

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, MSG_BUFFER_SIZE, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
