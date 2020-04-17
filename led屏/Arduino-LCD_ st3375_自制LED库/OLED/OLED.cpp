#include "OLED.h"


/******************************************************************************
      函数说明：创造对象
      入口数据：初始化显示屏
      返回值：  无
******************************************************************************/
OLED::OLED(int a,int b,int c,int d,int e){
            this->scl = a;
            this->sda = b;
            this->res = c;
            this->dc = d;
            this->cs = e;
            this->BACK_COLOR=WHITE;
}
/******************************************************************************
      函数说明：可以输出字符串
      入口数据：str 要打印的字符串
                x  起始纵坐标
                y  起始横坐标
                space 字符间隙
                size 字符大小 默认只支持16 或者32 可以自制字库
                color 字体颜色
      返回值：  无
******************************************************************************/
 void OLED::Lcd_String(String str,int x,int y,int space,int size,int color){
   for(int i= 0;i<str.length();i+=3){
     char n = str.charAt(i);
     char m = str.charAt(i+1);
     char o = str.charAt(i+2);
     int index = 0;
     String currFont;
     if(size == 16){
       currFont = chinese16;
     }else
     {
       currFont = chinese32;
     }
     
     for(int j= 0;j<currFont.length();j+=3){
        char g = currFont.charAt(j);
        char h = currFont.charAt(j+1);
        char k = currFont.charAt(j+2);
        if(n==g && m==h && o ==k){
           
            this->LCD_ShowChinese(x,y,index,size,color);
            x += (size+space);
            break;
        }
        index++;
     }
   }
  
 }

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void OLED::LCD_Writ_Bus(uint8_t dat) 
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
void OLED::LCD_WR_DATA8(uint8_t dat)
{
  OLED_DC_Set();//写数据
  LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void OLED::LCD_WR_DATA(short int dat)
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
void OLED::LCD_WR_REG(uint8_t dat)
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
void OLED::LCD_Address_Set(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)
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
void OLED::Lcd_Init(void)
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
void OLED::LCD_Clear(short int Color)
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
void OLED::LCD_ShowChinese(short int x,short int y,uint8_t index,uint8_t size,short int color)
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
void OLED::LCD_DrawPoint(short int x,short int y,short int color)
{
  LCD_Address_Set(x,y,x,y);//设置光标位置 
  LCD_WR_DATA(color);
} 


/******************************************************************************
      函数说明：LCD画一个大的点
      入口数据：x,y   起始坐标
      返回值：  无
******************************************************************************/
void OLED::LCD_DrawPoint_big(short int x,short int y,short int color)
{
  LCD_Fill(x-1,y-1,x+1,y+1,color);
} 


/******************************************************************************
      函数说明：在指定区域填充颜色
      入口数据：xsta,ysta   起始坐标
                xend,yend   终止坐标
      返回值：  无
******************************************************************************/
void OLED::LCD_Fill(short int xsta,short int ysta,short int xend,short int yend,short int color)
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
void OLED::LCD_DrawLine(short int x1,short int y1,short int x2,short int y2,short int color)
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
void OLED::LCD_DrawRectangle(short int x1, short int y1, short int x2, short int y2,short int color)
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
void OLED::Draw_Circle(short int x0,short int y0,uint8_t r,short int color)
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
void OLED::LCD_ShowChar(short int x,short int y,uint8_t num,short int color)
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
void OLED::LCD_ShowString(short int x,short int y,const char *p,short int color)
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
u32 OLED::mypow(uint8_t m,uint8_t n)
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
void OLED::LCD_ShowNum(short int x,short int y,short int num,uint8_t len,short int color)
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
void OLED::LCD_ShowNum1(short int x,short int y,float num,uint8_t len,short int color)
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
      //输出图片 起点为15,15 图片为96.这里需要写95
      //因为 图片向左偏移15.故95+15=110
******************************************************************************/
void OLED::LCD_ShowPicture(short int x1,short int y1,short int x2,short int y2)
{
  int i,j,temp1,temp2;
  LCD_Address_Set(x1,y1,x2,y2);
  for(i=0;i<9000;i++)
  {
    temp1=pgm_read_byte(&image[i*2+1]);
    temp2=pgm_read_byte(&image[i*2]);
    LCD_WR_DATA8(temp1);
    LCD_WR_DATA8(temp2);
  }     
}
