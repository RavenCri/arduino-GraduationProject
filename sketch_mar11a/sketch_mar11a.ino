#include <SoftwareSerial.h>
//实例化软串口
SoftwareSerial espSerial(0, 1); // RX, TX
int j;
char array[100];
void setup() {
 
  pinMode(13, OUTPUT);
  Serial.begin(9600); //设置波特率为9600，一般是这个波特率
  
  espSerial.begin(9600);
  //Serial.write("接收的软串口数据将显示在控制台\n");
}
int num = 0;
void loop() {
  
  espSerial.println("1");
 // delay(1000);
 
  while(espSerial.available() > 0){
     Serial.write(espSerial.read());
     Serial.print("读取软串口数据");
     Serial.println((++num));
     Serial.print("可用字节:");
     Serial.println(espSerial.available());
  }
 
  j = Serial.available();
  //如果串口有数据进入的话
  if(j != 0)
  {
    char ch = Serial.read();
    if(ch == '0'){
      digitalWrite(13,LOW);
    }else if(ch == '1'){
      digitalWrite(13,HIGH);
    }
    Serial.write("串口接收:");
    Serial.write(ch);
    Serial.write("\n");
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
