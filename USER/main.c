#include "delay.h"
#include "key.h"
#include "usart.h"
#include "gps.h"
#include "lcd.h"
#include "tools.h"
#include "mmc_sd.h"
#include "alarm.h"
#include "fontupd.h"
#include "text.h"
#include "ebook.h"

/*
gps :
	串口2  PA2,3
	按键   PA0,15 PC5
*/
void System_init()
{
	delay_init();
	uart_init(9600);
	uart2_init(115200);
	KEY_Init();
	LCD_Init();
	//SD_Initialize();
	font_init();		//中文
	alarm_init();
	ebook_init();
}


int main(void)
{
	System_init();
	while(1)
	{
		//Show_Str(0,0,240,20,"跌倒检测系统的特色在于实时性强，准确率高。阈值检测算法是我们根据论文与实验相结合而产生的高效算法。",16,0);
		//alarm_start();
		//gps_start();
		//ebook_start();
	}
	return 0;
}