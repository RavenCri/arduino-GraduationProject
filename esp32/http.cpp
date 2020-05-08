#include  "http.h"
#include "file.h"
FileService fileService;
AsyncWebServer server(80);
void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}
//启动web服务器
void HttpService::startWebServer(){
    
    server.serveStatic("/", SPIFFS, "/").setDefaultFile("index.html");
    server.on("/update", HTTP_POST, [] (AsyncWebServerRequest *request) {
        int params = request->params();
        for(int i = 0;i < params;i++){
           device_jSON[request->getParam(i)->name().c_str()] = request->getParam(i)->value();
        }
        Serial.println(device_jSON);
        //保存用户提交的数据
        boolean flag = fileService.writeFile("/data.json",JSON.stringify(device_jSON));
        if(flag){
          request->send(200, "text/plain", "ok");
        }else{
          request->send(200, "text/plain", "error");
        }
   });
   server.onNotFound(notFound);
   server.begin();
   common.s_print("web服务已开启!");
}

String HttpService::postRequest(String url,String postData){
  String contentType = "application/x-www-form-urlencoded";
   WiFiClient espClient;
   HttpClient httpClient = HttpClient(espClient,device_jSON["publicAddress"], 5500);
   httpClient.post(url, contentType, postData);
   int statusCode = httpClient.responseStatusCode();
   String response = httpClient.responseBody();
   if( statusCode == 200){
      return response;
   }else{
      return "error";
   }
}


void HttpService::heartPackage(){
 
    WiFiClient wifi;
    HttpClient httpClient = HttpClient(wifi, device_jSON["publicAddress"], 5500);
    String deviceId = JSON.stringify(device_jSON["deviceId"]);
    deviceId.replace("\"","");
    httpClient.get("/device/keepOnline?deviceId="+deviceId);
    Serial.print("发送心跳包...ResponseCode:");
    //必须加个响应阻塞一下 要不然直接就跳过了
    Serial.println(httpClient.responseStatusCode());
    //client.publish("outTopic", msg);
 
}  
