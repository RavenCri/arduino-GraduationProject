#ifndef HTTP_H
#define HTTP_H
//web服务器库
#include <ESPAsyncWebServer.h>
//web请求库
#include <ArduinoHttpClient.h>
#include <WiFi.h>
#include <AsyncTCP.h>

extern boolean connectFlag;
void notFound(AsyncWebServerRequest *request);
class HttpService{
  public:

    void startWebServer();
    String postRequest(String url,String da);
    void heartPackage();
};
#endif
