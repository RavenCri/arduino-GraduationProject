#include "common.h"

void Common::s_print(String str){
  Serial.println(str);
  arduinoSerial.print(str);
}
String Common::getPostData(JSONVar data){
    String res = "";
    JSONVar keys = data.keys();
    for (int i = 0; i < keys.length(); i++) {
      String key = (const char *)keys[i];
      String value = (const char *)data[keys[i]];
      res +=( key+"="+value);
      if( i < keys.length() -1 ){
        res += "&";
      }
    }
    return res;
}
String Common::getIP(IPAddress ip)//获取UDP 广播地址
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
