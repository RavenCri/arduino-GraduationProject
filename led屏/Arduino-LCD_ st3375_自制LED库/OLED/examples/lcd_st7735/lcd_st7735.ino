#include "OLED.h"
OLED oled(8,9,10,11,12);//scl sda res dc cs
void setup()
{
  Serial.begin(115200);
  oled.Lcd_Init();
  oled.LCD_Clear(WHITE);
}

void loop()
{
        /**
         * 输出汉字字符串
         * 第1个参数代表要输出的字符串 
         * 第2.3个为字符串初始坐标 
         * 第4个字符间隙（内部算法已包括了字体大小，间隙可以用在分散字符串）
         * 第5个为字体大小 只支持32和16的
         *       ps：如果需要用到输出汉字字符串，本身自带的我只弄了几个汉字，
         *      如果需要输出其他汉字，需要自制字库，然后更新到font.h的32位字库或者16位字库中。
         * 第6个为字体颜色 具体颜色可以看font.h定义好的
         */
        oled.Lcd_String("科睿出品",0,10,0,32,GREEN);
        oled.Lcd_String("合肥学院贡",10,50,5,16,GREEN);
        oled.Lcd_String("献社区力量",10,70,5,16,GREEN);
        //输出ascii字符串
        oled.LCD_ShowString(22,90,"num:",RED); 
        int num = 520;
        /*
         * 输出数字
         * 第1.2个为初始位置
         * 第3个为输出的数字
         * 第四个为输出的数字个数
         * 第五个为字体颜色
         *
         */
        oled.LCD_ShowNum(62,90,num,3,RED);
        char s[6];
        /**
         * 将小数转为字符串
         * 第一个参数为 要转化的小数
         * 第二个参数为数字总长度（包括小数点）
         * 第三个参数为小数点后保留几位
         * 第四个参数为把格式化后的字符保留在哪个空间里。
         */
        dtostrf(1.255,5,3,s); 
        /**
         * 输出小数
         * 第一二个为初始位置
         * 第三个为格式化好的字符串
         * 第四个为颜色。
         */
        oled.LCD_ShowString(10,110,"float:",RED); 
        oled.LCD_ShowString(70,110,s,RED);
        delay(3000);
        oled.LCD_Clear(WHITE);

}
