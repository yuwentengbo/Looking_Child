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
	����2  PA2,3
	����   PA0,15 PC5
*/
void System_init()
{
	delay_init();
	uart_init(9600);
	uart2_init(115200);
	KEY_Init();
	LCD_Init();
	//SD_Initialize();
	font_init();		//����
	alarm_init();
	ebook_init();
}


int main(void)
{
	System_init();
	while(1)
	{
		//Show_Str(0,0,240,20,"�������ϵͳ����ɫ����ʵʱ��ǿ��׼ȷ�ʸߡ���ֵ����㷨�����Ǹ���������ʵ�����϶������ĸ�Ч�㷨��",16,0);
		//alarm_start();
		//gps_start();
		//ebook_start();
	}
	return 0;
}