#include <MsTimer2.h>     //定时器库的头文件
#include "OLED.h"
OLED oled(8,9,10,11,12);
int tick = 0; //计数值
 
//中断服务程序
void onTimer()
{
  Serial.print("timer ");
  Serial.println(tick++);
}
 
void setup()
{
  Serial.begin(115200); //初始化串口
  oled.Lcd_Init();
  oled.LCD_Clear(WHITE);
  //MsTimer2::set(200, onTimer); //设置中断，每1000ms进入一次中断服务程序 onTimer()
  //MsTimer2::start(); //开始计时
}
 
void loop()
{
   int cuurY = oled.Lcd_String("指导lcd_sds_sd老师565语音识别123",0,10,0,16,GREEN);
   cuurY = oled.Lcd_String("雷文珲谢宇",0,cuurY,0,32,GREEN);
    oled.Lcd_String("雷文珲谢宇",0,cuurY,0,32,GREEN);
   //oled.LCD_ShowString(22,50,"lcd_0_1abAfFD",RED); 
   //oled.LCD_ShowPicture(15,15,110,110);
   delay(3000);
   oled.LCD_Clear(WHITE);
   
}
