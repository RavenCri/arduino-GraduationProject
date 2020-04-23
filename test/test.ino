#include <MsTimer2.h>     //定时器库的头文件
#include "OLED.h"
#include <Arduino_JSON.h>
OLED oled(8,9,10,11,12);
int tick = 0; //计数值
#define espSerial Serial2
JSONVar json ;
void setup()
{
  Serial.begin(115200); //初始化串口
  Serial2.begin(4800);
  json["username"] = "admin";
  json["deviceId"] = "0000-0000-0000-0001";
  json["deviceKey"] = "at037zf1jh28xl9t";
  json["fromType"] = "web";
  json["message"] = "房间温度：25°,二氧化碳浓度：25ml/L";
  
}
 
void loop()
{
   
   Serial2.print(JSON.stringify(json));
   delay(2000);
   
}
