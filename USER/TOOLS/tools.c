#include "tools.h"

void Lcd_Show_Float(u16 x,u16 y,float f)
{
	int i,j;
	i = (int)f;
	j = (f - i) *100000;
	LCD_ShowNum(x,y,i,5,16);
	LCD_ShowChar(x+100,y,',',16,1);
	x = x + 100;
	LCD_ShowNum(x,y,j,6,16);
}