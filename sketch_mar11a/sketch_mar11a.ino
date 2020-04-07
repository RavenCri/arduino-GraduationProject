#include <SoftwareSerial.h>
//实例化软串口
//SoftwareSerial espSerial(15, 14); // RX, TX
#define espSerial Serial3
const int leds[5] = {10,11,12,13};
const int ledLength = sizeof(leds)/sizeof(leds[0]);
int j;
char array[100];
String data;
void setup() {
 
  pinMode(13, OUTPUT);
  Serial.begin(9600); //设置波特率为9600，一般是这个波特率
  
  espSerial.begin(9600);
  //Serial.write("接收的软串口数据将显示在控制台\n");
}
int num = 0;
void loop() {
  
 // espSerial.println("1");
 // delay(1000);
 
  while(espSerial.available() > 0){
     Serial.write(espSerial.read());
 
  }
 
  j = Serial.available();
  //如果串口有数据进入的话
  if(j != 0)
  {
    data = "";
    while( Serial.available()>0 ){
       data += char(Serial.read());
       delay(100);
    }
    int index = data.indexOf("_");
    int type = data.substring(0,index).toInt();
    int motion = data.substring(index+1).toInt();
     digitalWrite(leds[type], motion);
    /*for(int i = 0; i<j; i++){
      //每次读一个字符，是ASCII码的
      array[i] = Serial.read();
    }
     //可以将输入的字符直接转化为数字
     //int val = strtol(array,NULL,10);
     // 控制led灯
     if(strcmp(array,"0") == 0){
       digitalWrite(13,LOW);
       Serial.println("收到关灯指令");
     }else if(strcmp(array,"1") == 0){
       digitalWrite(13,HIGH);
       Serial.println("收到开灯指令");
     }
      Serial.print("串口接收:");
      Serial.println(array);*/
  }
   

    
  
     // analogRead(A0)*(5.0/1023) 读取模拟信号的值 
    
     // 13号口会根据val的值来定义对应的“占空比”
      /*for(int i = 0; i <= 255; i++){
        analogWrite(13,i);
        delay(10);
      }
      for(int i = 255; i >= 0; i--){
        analogWrite(13,i);
        delay(10);
      }*/
}
