
#include "arduino.h"
#include "font.h"
#include "stdlib.h"
class OLED{
      public:
            int BACK_COLOR; 
            int POINT_COLOR;
            OLED(int a,int b,int c,int d,int e);
            void Lcd_String(String str,int x,int y,int space,int size,int color);
            void LCD_Writ_Bus(uint8_t dat);
            void LCD_WR_DATA8(uint8_t dat);
            void LCD_WR_DATA(short int dat);
            void LCD_WR_REG(uint8_t dat);
            void LCD_Address_Set(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
            void Lcd_Init(void);
            void LCD_Clear(short int Color);
            void LCD_ShowChinese(short int x,short int y,uint8_t index,uint8_t size,short int color);
            void LCD_DrawPoint(short int x,short int y,short int color);
            void LCD_DrawPoint_big(short int x,short int y,short int color);
            void LCD_Fill(short int xsta,short int ysta,short int xend,short int yend,short int color);
            void LCD_DrawLine(short int x1,short int y1,short int x2,short int y2,short int color);
            void LCD_DrawRectangle(short int x1, short int y1, short int x2, short int y2,short int color);
            void Draw_Circle(short int x0,short int y0,uint8_t r,short int color);
            void LCD_ShowChar(short int x,short int y,uint8_t num,short int color);
            void LCD_ShowString(short int x,short int y,const char *p,short int color);
            u32 mypow(uint8_t m,uint8_t n);
            void LCD_ShowNum(short int x,short int y,short int num,uint8_t len,short int color);
            void LCD_ShowNum1(short int x,short int y,float num,uint8_t len,short int color);
            void LCD_ShowPicture(short int x1,short int y1,short int x2,short int y2);
      private:
            int scl;
            int sda;
            int res;
            int dc;
            int cs;
            
          
};
