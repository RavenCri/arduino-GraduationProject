
//实例化软串口
//SoftwareSerial espSerial(15, 14); // RX, TX
#define espSerial Serial3
const int leds[5] = {10,11,12,13};
const int ledLength = sizeof(leds)/sizeof(leds[0]);
int j;
char array[100];
String data;
#include "MD5.h"
void setup() {
  Serial.begin(115200);
 unsigned char* hash=MD5::make_hash("hello world");
  //generate the digest (hex encoding) of our hash
 char *md5str = MD5::make_digest(hash, 16);
 Serial.println(md5str);
}
int num = 0;
void loop() {
  
 
}
