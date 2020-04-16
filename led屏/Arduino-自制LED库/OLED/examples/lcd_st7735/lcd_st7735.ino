#include "OLED.h"
#include "font.h"
OLED oled(8,9,10,11,12);//scl sda res dc cs
void setup()
{
  oled.Lcd_Init();
  oled.LCD_Clear(WHITE);
           
 
}

void loop()
{
      oled.LCD_ShowChinese(0,0,0,32,MAGENTA);   //合肥学院
      oled.LCD_ShowChinese(32,0,1,32,LIGHTBLUE);   
      oled.LCD_ShowChinese(64,0,2,32,BRRED);   
      oled.LCD_ShowChinese(96,0,3,32,GREEN);    
        
      oled.LCD_ShowChinese(40,40,4,16,RED);  //毕设题目
      oled.LCD_ShowChinese(56,40,5,16,RED);   
      oled.LCD_ShowChinese(72,40,6,16,RED);  
      oled.LCD_ShowChinese(88,40,7,16,RED); 

      oled.LCD_ShowChinese(10,60,8,16,GREEN);  //基于语音识别的远程控制系统设计
      oled.LCD_ShowChinese(26,60,9,16,GREEN);   
      oled.LCD_ShowChinese(42,60,10,16,GREEN);  
      oled.LCD_ShowChinese(58,60,11,16,GREEN); 
      oled.LCD_ShowChinese(74,60,12,16,GREEN);  
      oled.LCD_ShowChinese(90,60,13,16,GREEN);   
      oled.LCD_ShowChinese(106,60,14,16,GREEN);  

      oled.LCD_ShowChinese(16,76,15,16,GREEN);  
      oled.LCD_ShowChinese(32,76,16,16,GREEN);   
      oled.LCD_ShowChinese(48,76,17,16,GREEN);  
      oled.LCD_ShowChinese(64,76,18,16,GREEN); 
      oled.LCD_ShowChinese(80,76,19,16,GREEN);  
      oled.LCD_ShowChinese(96,76,20,16,GREEN);
         
      oled.LCD_ShowChinese(48,92,21,16,GREEN);
      oled.LCD_ShowChinese(64,92,22,16,GREEN);
      
       // LCD_ShowString(22,60,"1.44 TFT SPI",RED);
      //LCD_ShowNum(82,80,LCD_W,3,RED);
      delay(3000);
      oled.LCD_Clear(WHITE);

      oled.LCD_ShowChinese(10,10,46,16,RED);  //系统设计：
      oled.LCD_ShowChinese(26,10,47,16,RED);   
      oled.LCD_ShowChinese(42,10,21,16,RED);  
      oled.LCD_ShowChinese(58,10,22,16,RED); 
      oled.LCD_ShowChinese(88,10,30,16,RED); 
      
      oled.LCD_ShowChinese(20,30,4,32,RED);   //雷文珲
      oled.LCD_ShowChinese(52,30,5,32,RED);   
      oled.LCD_ShowChinese(84,30,6,32,RED); 
      
      oled.LCD_ShowChinese(10,70,26,16,GREEN);  //指导老师：
      oled.LCD_ShowChinese(26,70,27,16,GREEN);   
      oled.LCD_ShowChinese(42,70,28,16,GREEN);  
      oled.LCD_ShowChinese(58,70,29,16,GREEN); 
      oled.LCD_ShowChinese(88,70,30,16,GREEN); 
      
      oled.LCD_ShowChinese(30,90,7,32,RED);   //谢宇
      oled.LCD_ShowChinese(72,90,8,32,RED);   
      delay(3000);
      oled.LCD_Clear(WHITE);
}