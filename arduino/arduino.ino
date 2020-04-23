#include <Arduino_JSON.h>

#include "OLED.h"
#include "Queue.h"

#include <MsTimer2.h>     //定时器库的头文件
//esp串口数据写入tx2 应该用Serial2
#define espSerial Serial2

// 电机引脚
const int djz = 2;
const int djf = 3;
const int leds[5] = {13,0,0,0,0};
const int ledLength = sizeof(leds)/sizeof(leds[0]);
//默认风扇转速
int aroundSpeed = 100;
//消息队列
DataQueue<String> intQueue(200);
DataQueue<String> handledQueue(200);
//当前显示屏显示的纵坐标
int currY = 0;
boolean flagShow = false;

OLED oled(8,9,10,11,12);//scl sda res dc cs

void setup() {
  Serial.begin(115200);
  // 波特率应该跟esp发送区设置的一样大
  espSerial.begin(4800);
  init_Interrupt();
  //初始化IO口
  init_IO();
  

}
void loop() {
  //初始化显示屏
  if(!flagShow){
    init_LCD();
  }else{
    if (!handledQueue.isEmpty()) {
     String data = handledQueue.dequeue();
    
     Serial.println("要显示->"+data);
     if(currY >=128){
           currY = 0;
           oled.LCD_Clear(WHITE);
        }   
     currY= oled.Lcd_String("收到："+data,10,currY,0,16,DARKBLUE);
    }
  }
  
}
void init_LCD()
{
//   oled.Lcd_Init();
//   oled.LCD_Clear(WHITE);
//   oled.LCD_ShowPicture(15,15,110,110);
//   oled.LCD_Clear(WHITE);
//   oled.Lcd_String("合",0,0,0,32,MAGENTA);   
//   oled.Lcd_String("肥",32,0,0,32,LIGHTBLUE);   
//   oled.Lcd_String("学",64,0,0,32,BRRED);   
//   oled.Lcd_String("院",96,0,0,32,GREEN); 
//   oled.Lcd_String("毕设题目：",20,40,10,16,LIGHTGREEN);
//   oled.Lcd_String("基于语音识别的",10,60,0,16,LGRAYBLUE);
//   oled.Lcd_String("远程",50,76,0,16,LGRAYBLUE);
//   oled.Lcd_String("控制系统设计",20,95,0,16,BROWN);
//   oled.LCD_Clear(WHITE);
//   oled.Lcd_String("系统设计：",10,10,5,16,RED);
//   oled.Lcd_String("雷文珲",20,30,0,32,LIGHTBLUE);
//   oled.Lcd_String("指导老师：",10,70,5,16,RED);
//   oled.Lcd_String("谢宇",30,90,0,32,DARKBLUE);
//   currY = 128;
   flagShow = true;
}
void init_IO()
{
  pinMode(djz, OUTPUT);
  pinMode(djf, OUTPUT);
  for(int i = 0; i< ledLength; i++){
    if(leds[i] !=0)
      pinMode(leds[i], OUTPUT);
  }
}
void init_Interrupt(){
  MsTimer2::set(200, onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  MsTimer2::start(); //开始计时
}
//中断服务程序
void onTimer()
{
  //接收消息
  reviceMsg();
  //处理消息
  handleMsg(); 
}
/*'
 * 接收消息
 */


void reviceMsg(){
  String data = "";
  if( espSerial.available()>0 ){
    delay(200);
    char c;
    c = espSerial.read();
    if(c != '@'){
      return;  
    }
    while( (c = espSerial.read()) !='$' ){
       Serial.print(c);
       data += c;  
       if(((int)c) == -1)return;
       delay(20);
    }

    Serial.println(("收到esp："+data));
    intQueue.enqueue(data);
  
    //  while( espSerial.available()>0  ){
    //       c = espSerial.read();
    //       data += c;  
    //    }
   
   }
}
/**
 * 处理消息
 */
void handleMsg(){
  if (!intQueue.isEmpty()) {
    String data = intQueue.dequeue();
    JSONVar json_data = JSON.parse(data);
    String  code = (const char *)json_data["code"];
    String  platForm = (const char *)json_data["platForm"];
    handledQueue.enqueue(data);
    int index = code.indexOf("_");
    String type = code.substring(0,index);
    String motion = code.substring(index+1);
    executeCmd(type,motion,platForm);
    
  }   
}
/**
 * 执行对应命令
 */
void executeCmd(String type,String motion,String platForm){
  if(type=="electricMachinery"){//操作电机
     int mot = motion.toInt();
     operationElectricMachinery(mot);
  }else if(type=="led"){//操作led灯
     int index = motion.indexOf("_");
     // 获取要操作几号灯
     int ledIndex = motion.substring(0,index).toInt();
     int mot = motion.substring(index+1).toInt();
     operationLED(ledIndex,mot);
  }else if(type == "measure"){//测量家居信号
     operationMeasure(platForm);
  }
}
/**
 * 控制电机
 */
void operationElectricMachinery(int motion){
   switch(motion){
    case 0: // 停止转动
         digitalWrite(djz, HIGH);
         digitalWrite(djf, HIGH);
          break;
    case 1: // 正向转动
          digitalWrite(djz,aroundSpeed );
          digitalWrite(djf, HIGH);
          break;
    case 2:// 反向转动
          digitalWrite(djz, HIGH);
          digitalWrite(djf, aroundSpeed);
          break;
    case 3: //加速转动
          aroundSpeed += 50;
          if(aroundSpeed  >255){
            Serial.println("达到最大转速阈值");
            aroundSpeed = 255;
          }
          digitalWrite(djf, aroundSpeed);
          break;
    case 4: //减速转动
          aroundSpeed -= 50;
          if(aroundSpeed  < 0 ){
            aroundSpeed = 10;
            Serial.println("达到最小转速阈值");
          }
          digitalWrite(djf, aroundSpeed);
          break;
  }
}
/**
 * 控制灯
 */
void operationLED(int ledIndex,int motion){
   
   switch(ledIndex){
    case 0: // 0号灯
          digitalWrite(leds[ledIndex], motion);
          break;
    case 1: // 1号灯
          digitalWrite(leds[ledIndex], motion);
          break;
    case 99: //操作所有灯
         for(int i = 0; i<ledLength; i++){
            digitalWrite(leds[i], motion);
            delay(10);
         }
          break;
  }
}
void operationMeasure(String platForm){
  JSONVar send;
  send["platForm"] = platForm;
  send["msg"] = "房间温度：25°,二氧化碳浓度：25ml/L";
  espSerial.print(JSON.stringify(send));
}
