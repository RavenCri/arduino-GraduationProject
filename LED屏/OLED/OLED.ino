//////////////////////////////////////////////////////////////////////////////////   
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//中景园电子
//店铺地址：https://oled-zjy.taobao.com/
//
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : HuangKai
//  生成日期   : 2019-3-19
//  最近修改   : 
//  功能描述   : arduino UNO LCD显示屏例程
//              说明: 
//              ----------------------------------------------------------------
//              GND  电源地
//              VCC  5v电源
//              SCL   8（SCL）
//              SDA   9（SDA）
//              RES   10
//              DC    11
//              CS    12 
//              BLK   不接
//              ----------------------------------------------------------------
// 修改历史   :
// 日    期   : 
// 作    者   : HuangKai
// 修改内容   : 创建文件
//版权所有，盗版必究。
//Copyright(C) 中景园电子2019-3-19
//All rights reserved
//******************************************************************************/
#include "font.h"

int scl=8;//定义数字接口8
int sda=9;//定义数字接口9
int res=10;//定义数字接口10
int dc=11;//定义数字接口11
int cs=12;//定义数字接口12

#define OLED_SCLK_Clr() digitalWrite(scl,LOW)//SCL
#define OLED_SCLK_Set() digitalWrite(scl,HIGH)

#define OLED_SDIN_Clr() digitalWrite(sda,LOW)//SDA
#define OLED_SDIN_Set() digitalWrite(sda,HIGH)

#define OLED_RST_Clr() digitalWrite(res,LOW)//RES
#define OLED_RST_Set() digitalWrite(res,HIGH)

#define OLED_DC_Clr()  digitalWrite(dc,LOW)//DC
#define OLED_DC_Set()  digitalWrite(dc,HIGH)
          
#define OLED_CS_Clr()  digitalWrite(cs,LOW)//CS
#define OLED_CS_Set()  digitalWrite(cs,HIGH)

#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 128

#else
#define LCD_W 128
#define LCD_H 128
#endif


//颜色
#define WHITE            0xFFFF
#define BLACK            0x0000
#define BLUE             0x001F  
#define BRED             0XF81F
#define GRED             0XFFE0
#define GBLUE            0X07FF
#define RED              0xF800
#define MAGENTA          0xF81F
#define GREEN            0x07E0
#define CYAN             0x7FFF
#define YELLOW           0xFFE0
#define BROWN            0XBC40 //棕色
#define BRRED            0XFC07 //棕红色
#define GRAY             0X8430 //灰色
//GUI颜色

#define DARKBLUE         0X01CF //深蓝色
#define LIGHTBLUE        0X7D7C //浅蓝色  
#define GRAYBLUE         0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN       0X841F //浅绿色
#define LGRAY            0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

short int BACK_COLOR, POINT_COLOR;
void setup()
{
  uint8_t m,i;
  float t=0;
  Lcd_Init();
  LCD_Clear(WHITE);
  BACK_COLOR=WHITE;
  while(1)
  {
      LCD_ShowChinese(0,0,0,32,MAGENTA);   //合肥学院
      LCD_ShowChinese(32,0,1,32,LIGHTBLUE);   
      LCD_ShowChinese(64,0,2,32,BRRED);   
      LCD_ShowChinese(96,0,3,32,GREEN);    
        
      LCD_ShowChinese(40,40,4,16,RED);  //毕设题目
      LCD_ShowChinese(56,40,5,16,RED);   
      LCD_ShowChinese(72,40,6,16,RED);  
      LCD_ShowChinese(88,40,7,16,RED); 

      LCD_ShowChinese(10,60,8,16,GREEN);  //基于语音识别的远程控制系统设计
      LCD_ShowChinese(26,60,9,16,GREEN);   
      LCD_ShowChinese(42,60,10,16,GREEN);  
      LCD_ShowChinese(58,60,11,16,GREEN); 
      LCD_ShowChinese(74,60,12,16,GREEN);  
      LCD_ShowChinese(90,60,13,16,GREEN);   
      LCD_ShowChinese(106,60,14,16,GREEN);  

      LCD_ShowChinese(16,76,15,16,GREEN);  
      LCD_ShowChinese(32,76,16,16,GREEN);   
      LCD_ShowChinese(48,76,17,16,GREEN);  
      LCD_ShowChinese(64,76,18,16,GREEN); 
      LCD_ShowChinese(80,76,19,16,GREEN);  
      LCD_ShowChinese(96,76,20,16,GREEN);
         
      LCD_ShowChinese(48,92,21,16,GREEN);
      LCD_ShowChinese(64,92,22,16,GREEN);
      
       // LCD_ShowString(22,60,"1.44 TFT SPI",RED);
      //LCD_ShowNum(82,80,LCD_W,3,RED);
      delay(3000);
      LCD_Clear(WHITE);

      LCD_ShowChinese(10,10,46,16,RED);  //系统设计：
      LCD_ShowChinese(26,10,47,16,RED);   
      LCD_ShowChinese(42,10,21,16,RED);  
      LCD_ShowChinese(58,10,22,16,RED); 
      LCD_ShowChinese(88,10,30,16,RED); 
      
      LCD_ShowChinese(20,30,4,32,RED);   //雷文珲
      LCD_ShowChinese(52,30,5,32,RED);   
      LCD_ShowChinese(84,30,6,32,RED); 
      
      LCD_ShowChinese(10,70,26,16,GREEN);  //指导老师：
      LCD_ShowChinese(26,70,27,16,GREEN);   
      LCD_ShowChinese(42,70,28,16,GREEN);  
      LCD_ShowChinese(58,70,29,16,GREEN); 
      LCD_ShowChinese(88,70,30,16,GREEN); 
      
      LCD_ShowChinese(30,90,7,32,RED);   //谢宇
      LCD_ShowChinese(72,90,8,32,RED);   
      delay(3000);
      LCD_Clear(WHITE);
  }
}

void loop()
{
}













/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(uint8_t dat) 
{  
  uint8_t i; 
  OLED_CS_Clr();
  for(i=0;i<8;i++)
  {       
    OLED_SCLK_Clr();
    if(dat&0x80)
       OLED_SDIN_Set();
    else 
       OLED_SDIN_Clr();
    OLED_SCLK_Set();
    dat<<=1;   
  }   
  OLED_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(uint8_t dat)
{
  OLED_DC_Set();//写数据
  LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(short int dat)
{
  OLED_DC_Set();//写数据
  LCD_Writ_Bus(dat>>8);
  LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(uint8_t dat)
{
  OLED_DC_Clr();//写命令
  LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
{
  if(USE_HORIZONTAL==0)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+2);
    LCD_WR_DATA(x2+2);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+1);
    LCD_WR_DATA(y2+1);
    LCD_WR_REG(0x2c);//储存器写
  }
  else if(USE_HORIZONTAL==1)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+2);
    LCD_WR_DATA(x2+2);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+3);
    LCD_WR_DATA(y2+3);
    LCD_WR_REG(0x2c);//储存器写
  }
  else if(USE_HORIZONTAL==2)
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+1);
    LCD_WR_DATA(x2+1);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+2);
    LCD_WR_DATA(y2+2);
    LCD_WR_REG(0x2c);//储存器写
  }
  else
  {
    LCD_WR_REG(0x2a);//列地址设置
    LCD_WR_DATA(x1+3);
    LCD_WR_DATA(x2+3);
    LCD_WR_REG(0x2b);//行地址设置
    LCD_WR_DATA(y1+2);
    LCD_WR_DATA(y2+2);
    LCD_WR_REG(0x2c);//储存器写
  }
}


//OLED的初始化
void Lcd_Init(void)
{
  pinMode(scl,OUTPUT);//设置数字8
  pinMode(sda,OUTPUT);//设置数字9
  pinMode(res,OUTPUT);//设置数字10
  pinMode(dc,OUTPUT);//设置数字11
  pinMode(cs,OUTPUT);//设置数字12
  
  OLED_RST_Set();
  delay(100);
  OLED_RST_Clr();//复位
  delay(200);
  OLED_RST_Set();
  delay(100);


//************* Start Initial Sequence **********//
LCD_WR_REG(0x11); //Sleep out
delay(120); //Delay 120ms
//------------------------------------ST7735S Frame rate-------------------------------------------------//
LCD_WR_REG(0xB1); //Frame rate 80Hz
LCD_WR_DATA8(0x02);
LCD_WR_DATA8(0x35);
LCD_WR_DATA8(0x36);
LCD_WR_REG(0xB2); //Frame rate 80Hz
LCD_WR_DATA8(0x02);
LCD_WR_DATA8(0x35);
LCD_WR_DATA8(0x36);
LCD_WR_REG(0xB3); //Frame rate 80Hz
LCD_WR_DATA8(0x02);
LCD_WR_DATA8(0x35);
LCD_WR_DATA8(0x36);
LCD_WR_DATA8(0x02);
LCD_WR_DATA8(0x35);
LCD_WR_DATA8(0x36);
//------------------------------------End ST7735S Frame rate-------------------------------------------//
LCD_WR_REG(0xB4); //Dot inversion
LCD_WR_DATA8(0x03);
//------------------------------------ST7735S Power Sequence-----------------------------------------//
LCD_WR_REG(0xC0);
LCD_WR_DATA8(0xA2);
LCD_WR_DATA8(0x02);
LCD_WR_DATA8(0x84);
LCD_WR_REG(0xC1);
LCD_WR_DATA8(0xC5);
LCD_WR_REG(0xC2);
LCD_WR_DATA8(0x0D);
LCD_WR_DATA8(0x00);
LCD_WR_REG(0xC3);
LCD_WR_DATA8(0x8D);
LCD_WR_DATA8(0x2A);
LCD_WR_REG(0xC4);
LCD_WR_DATA8(0x8D);
LCD_WR_DATA8(0xEE);
//---------------------------------End ST7735S Power Sequence---------------------------------------//
LCD_WR_REG(0xC5); //VCOM
LCD_WR_DATA8(0x0a);
LCD_WR_REG(0x36);
if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
else LCD_WR_DATA8(0xA8);
//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
LCD_WR_REG(0XE0);
LCD_WR_DATA8(0x12);
LCD_WR_DATA8(0x1C);
LCD_WR_DATA8(0x10);
LCD_WR_DATA8(0x18);
LCD_WR_DATA8(0x33);
LCD_WR_DATA8(0x2C);
LCD_WR_DATA8(0x25);
LCD_WR_DATA8(0x28);
LCD_WR_DATA8(0x28);
LCD_WR_DATA8(0x27);
LCD_WR_DATA8(0x2F);
LCD_WR_DATA8(0x3C);
LCD_WR_DATA8(0x00);
LCD_WR_DATA8(0x03);
LCD_WR_DATA8(0x03);
LCD_WR_DATA8(0x10);
LCD_WR_REG(0XE1);
LCD_WR_DATA8(0x12);
LCD_WR_DATA8(0x1C);
LCD_WR_DATA8(0x10);
LCD_WR_DATA8(0x18);
LCD_WR_DATA8(0x2D);
LCD_WR_DATA8(0x28);
LCD_WR_DATA8(0x23);
LCD_WR_DATA8(0x28);
LCD_WR_DATA8(0x28);
LCD_WR_DATA8(0x26);
LCD_WR_DATA8(0x2F);
LCD_WR_DATA8(0x3B);
LCD_WR_DATA8(0x00);
LCD_WR_DATA8(0x03);
LCD_WR_DATA8(0x03);
LCD_WR_DATA8(0x10);
//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
LCD_WR_REG(0x3A); //65k mode
LCD_WR_DATA8(0x05);
LCD_WR_REG(0x29); //Display on 
}


/******************************************************************************
      函数说明：LCD清屏函数
      入口数据：无
      返回值：  无
******************************************************************************/
void LCD_Clear(short int Color)
{
  short int i,j;    
  LCD_Address_Set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_H;i++)
    {
       for (j=0;j<LCD_W;j++)
        {
          LCD_WR_DATA(Color);
        }

    }
}


/******************************************************************************
      函数说明：LCD显示汉字
      入口数据：x,y   起始坐标
                index 汉字的序号
                size  字号
      返回值：  无
******************************************************************************/
void LCD_ShowChinese(short int x,short int y,uint8_t index,uint8_t size,short int color)
{  
  uint8_t i,j,x1=x;
  uint8_t temp,size1;
  LCD_Address_Set(x,y,x+size-1,y+size-1);//设置一个汉字的区域
  size1=size*size/8;//一个汉字所占的字节
  temp+=index*size1;//写入的起始位置
  for(j=0;j<size1;j++)
  {
    if(size==16)
        temp=pgm_read_byte(&Hzk16[index*size1+j]);//选择16x16字号
    if(size==32)
        temp=pgm_read_byte(&Hzk32[index*size1+j]);//选择32x32字号
    for(i=0;i<8;i++)
    {
      if(temp&(1<<i))//从数据的低位开始读
        LCD_WR_DATA(color);//点亮
      else
        LCD_WR_DATA(BACK_COLOR);
    }
    temp++;
   }
}


/******************************************************************************
      函数说明：LCD显示汉字
      入口数据：x,y   起始坐标
      返回值：  无
******************************************************************************/
void LCD_DrawPoint(short int x,short int y,short int color)
{
  LCD_Address_Set(x,y,x,y);//设置光标位置 
  LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：LCD画一个大的点
      入口数据：x,y   起始坐标
      返回值：  无
******************************************************************************/
void LCD_DrawPoint_big(short int x,short int y,short int color)
{
  LCD_Fill(x-1,y-1,x+1,y+1,color);
} 


/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
      返回值：  无
******************************************************************************/
void LCD_Fill(short int xsta,short int ysta,short int xend,short int yend,short int color)
{          
  short int i,j; 
  LCD_Address_Set(xsta,ysta,xend,yend);      //设置光标位置 
  for(i=ysta;i<=yend;i++)
  {                               
    for(j=xsta;j<=xend;j++)
    {
      LCD_WR_DATA(color);//设置光标位置     
    }     
  }                   
}


/******************************************************************************
      函数说明：画线
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
      返回值：  无
******************************************************************************/
void LCD_DrawLine(short int x1,short int y1,short int x2,short int y2,short int color)
{
  short int t; 
  int xerr=0,yerr=0,delta_x,delta_y,distance;
  int incx,incy,uRow,uCol;
  delta_x=x2-x1; //计算坐标增量 
  delta_y=y2-y1;
  uRow=x1;//画线起点坐标
  uCol=y1;
  if(delta_x>0)incx=1; //设置单步方向 
  else if (delta_x==0)incx=0;//垂直线 
  else {incx=-1;delta_x=-delta_x;}
  if(delta_y>0)incy=1;
  else if (delta_y==0)incy=0;//水平线 
  else {incy=-1;delta_y=-delta_x;}
  if(delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
  else distance=delta_y;
  for(t=0;t<distance+1;t++)
  {
    LCD_DrawPoint(uRow,uCol,color);//画点
    xerr+=delta_x;
    yerr+=delta_y;
    if(xerr>distance)
    {
      xerr-=distance;
      uRow+=incx;
    }
    if(yerr>distance)
    {
      yerr-=distance;
      uCol+=incy;
    }
  }
}


/******************************************************************************
      函数说明：画矩形
      入口数据：x1,y1   起始坐标
                x2,y2   终止坐标
      返回值：  无
******************************************************************************/
void LCD_DrawRectangle(short int x1, short int y1, short int x2, short int y2,short int color)
{
  LCD_DrawLine(x1,y1,x2,y1,color);
  LCD_DrawLine(x1,y1,x1,y2,color);
  LCD_DrawLine(x1,y2,x2,y2,color);
  LCD_DrawLine(x2,y1,x2,y2,color);
}


/******************************************************************************
      函数说明：画圆
      入口数据：x0,y0   圆心坐标
                r       半径
      返回值：  无
******************************************************************************/
void Draw_Circle(short int x0,short int y0,uint8_t r,short int color)
{
  int a,b;
  int di;
  a=0;b=r;    
  while(a<=b)
  {
    LCD_DrawPoint(x0-b,y0-a,color);             //3           
    LCD_DrawPoint(x0+b,y0-a,color);             //0           
    LCD_DrawPoint(x0-a,y0+b,color);             //1                
    LCD_DrawPoint(x0-a,y0-b,color);             //2             
    LCD_DrawPoint(x0+b,y0+a,color);             //4               
    LCD_DrawPoint(x0+a,y0-b,color);             //5
    LCD_DrawPoint(x0+a,y0+b,color);             //6 
    LCD_DrawPoint(x0-b,y0+a,color);             //7
    a++;
    if((a*a+b*b)>(r*r))//判断要画的点是否过远
    {
      b--;
    }
  }
}


/******************************************************************************
      函数说明：显示字符
      入口数据：x,y    起点坐标
                num    要显示的字符
                color  颜色
      返回值：  无
******************************************************************************/
void LCD_ShowChar(short int x,short int y,uint8_t num,short int color)
{
  uint8_t pos,t,temp;
  short int x1=x;
  if(x>LCD_W-16||y>LCD_H-16)return;     //设置窗口       
  num=num-' ';//得到偏移后的值
  LCD_Address_Set(x,y,x+8-1,y+16-1);      //设置光标位置 
    for(pos=0;pos<16;pos++)
    {
       temp=pgm_read_byte(&asc2_1608[num*16+pos]);   //调用1608字体
//        temp=asc2_1608[(short int)num*16+pos];     //调用1608字体
       for(t=0;t<8;t++)
        {
            if(temp&0x01)LCD_DrawPoint(x+t,y+pos,color);//画一个点
            else LCD_DrawPoint(x+t,y+pos,WHITE);
            temp>>=1;
        }
    }
}


/******************************************************************************
      函数说明：显示字符串
      入口数据：x,y    起点坐标
                *p     字符串起始地址
      返回值：  无
******************************************************************************/
void LCD_ShowString(short int x,short int y,const char *p,short int color)
{         
    while(*p!='\0')
    {       
        if(x>LCD_W-16){x=0;y+=16;}
        if(y>LCD_H-16){y=x=0;LCD_Clear(POINT_COLOR);}
        LCD_ShowChar(x,y,*p,color);
        x+=8;
        p++;
    }  
}


/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
u32 mypow(uint8_t m,uint8_t n)
{
  u32 result=1;
  while(n--)result*=m;    
  return result;
}


/******************************************************************************
      函数说明：显示数字
      入口数据：x,y    起点坐标
                num    要显示的数字
                len    要显示的数字个数
      返回值：  无
******************************************************************************/
void LCD_ShowNum(short int x,short int y,short int num,uint8_t len,short int color)
{           
  uint8_t t,temp;
  uint8_t enshow=0;
  for(t=0;t<len;t++)
  {
    temp=(num/mypow(10,len-t-1))%10;
    if(enshow==0&&t<(len-1))
    {
      if(temp==0)
      {
        LCD_ShowChar(x+8*t,y,' ',color);
        continue;
      }else enshow=1; 
       
    }
    LCD_ShowChar(x+8*t,y,temp+48,color); 
  }
} 

/******************************************************************************
      函数说明：显示数字
      入口数据：x,y    起点坐标
                num    要显示的数字
                len    要显示的数字个数
      返回值：  无
******************************************************************************/
void LCD_ShowNum1(short int x,short int y,float num,uint8_t len,short int color)
{           
  uint8_t t,temp;
  uint8_t enshow=0;
  short int num1;
  num1=num*100;
  for(t=0;t<len;t++)
  {
    temp=(num1/mypow(10,len-t-1))%10;
    if(t==(len-2))
    {
      LCD_ShowChar(x+8*(len-2),y,'.',color);
      t++;
      len+=1;
    }
    LCD_ShowChar(x+8*t,y,temp+48,color);
  }
}


/******************************************************************************
      函数说明：显示40x40图片
      入口数据：x,y    起点坐标
      返回值：  无
******************************************************************************/
void LCD_ShowPicture(short int x1,short int y1,short int x2,short int y2)
{
  int i,j,temp1,temp2;
  LCD_Address_Set(x1,y1,x2,y2);
  for(i=0;i<1600;i++)
  {
    temp1=pgm_read_byte(&image[i*2+1]);
    temp2=pgm_read_byte(&image[i*2]);
    LCD_WR_DATA8(temp1);
    LCD_WR_DATA8(temp2);
  }     
}
