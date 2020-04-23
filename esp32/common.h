
#ifndef COMMON_H
#define COMMON_H
//ArduinoJSON库
#include <Arduino_JSON.h>
#define arduinoSerial Serial2


class Common{
  public:
    void s_print(String str);
    String getIP(IPAddress ip);
    String getPostData(JSONVar data);
};
#endif
