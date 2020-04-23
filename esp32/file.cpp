#include "file.h"

Common common;
// 设备信息
JSONVar device_jSON;
void FileService::listDir(fs::FS &fs, const char * dirname, uint8_t levels){
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
void FileService::init(){
  Serial.println("文件列表：");
  listDir(SPIFFS, "/", 0);
  if(!SPIFFS.begin(true)){
     Serial.println("安装SPIFFS时发生错误...");
     return;
  }
  Serial.println("读取配置文件中...");
  File device_file = SPIFFS.open("/data.json",FILE_READ);
  if(!device_file || device_file.size()==0){
    common.s_print("配置文件不存在，即将创建配置文件...");  
    device_file.close();
    device_file = SPIFFS.open("/data.json", FILE_WRITE);
    if(!device_file){
        common.s_print("创建配置文件失败！");
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
    device_file = SPIFFS.open("/data.json");
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
boolean FileService::writeFile( const char * path, String message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = SPIFFS.open(path, FILE_WRITE);
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
