#ifndef FILE_H
#define FILE_H
#include "common.h"
// 文件操作库
#include "SPIFFS.h"
#include "FS.h"
extern JSONVar device_jSON;
extern Common common;
class FileService{
    public:
      void init();
      void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
      boolean writeFile(const char * path, String message);
};
#endif
