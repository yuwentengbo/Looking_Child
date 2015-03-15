#include "sys.h"
#include "24cxx.h"
#include "usart.h"
#include "lcd.h"

u8 time[6];
u8 alarm_time[6];
u8 alarm_flag = 0;
void alarm_init()
{
	AT24CXX_Init();
	alarm_time[0] = 20;
	alarm_time[1] = 15;
	alarm_time[2] = 1;
	alarm_time[3] = 1;
	alarm_time[4] = 0;
	alarm_time[5] = 0;
}

void alarm_start()
{
	 u8 test[2];
	 alarm_time[0] = 20;
	 alarm_time[1] = 3;	
	 AT24CXX_Write(0,(u8*)alarm_time,5);
	 AT24CXX_Read(0,(u8*)test,1);
	 printf("%d",test[0]);
}

void alarm_show()
{
	LCD_ShowNum(20,20,alarm_time[0],2,16);
	LCD_ShowNum(24,20,alarm_time[1],2,16);
	LCD_ShowNum(50,20,alarm_time[2],2,16);
	LCD_ShowNum(80,20,alarm_time[3],2,16);
	LCD_ShowNum(20,50,alarm_time[4],2,16);
	LCD_ShowNum(80,50,alarm_time[5],2,16);
}
	