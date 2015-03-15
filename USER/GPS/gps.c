#include "gps.h"
#include "usart.h"
#include "string.h"
#include "tools.h"

GPS_DATA gps_data;
u8 gps_rec[USART_REC_LEN];
extern u8 usart2_data[USART_REC_LEN];
extern u8 usart2_flag;
extern u16 usart2_index;
void gps_start()
{
	gps_getdata();
	Lcd_Show_Float(20,20,gps_data.latitude);
	Lcd_Show_Float(20,50,gps_data.longitude);
}

void gps_getdata()
{
	u16 i;
	if(usart2_flag == 1)
	{
		for(i = 0;i < USART_REC_LEN;i++)
			gps_rec[i] = usart2_data[i];
		for(i = 0;i < USART_REC_LEN;i++)
			usart2_data[i] = 0;
		Gps_Gpgll_Process();
		usart2_flag = 0;
		usart2_index = 0;
	}
}

void Gps_Gpgll_Process()
{
	u8 *p ,*p1;
	int i = 0;
	float longitude= 0,latitude = 0,x = 0,y = 10.0;
	char longitude_n,latitude_n;
	p = (u8 *)strstr((char *)gps_rec,"GPGLL");
	if(p != NULL)
	{
		p1 = p;
		while(1)
		{
			if(i == 6) break;
			if(*p1 == ',') i++;
			p1++;
		}
		p1++;
		if(*p1 == 'A')		// 有效定位
		{
			p = p + 6;
			latitude = (*p - '0') * 10.0;
			p++;
			latitude += (*p - '0');
			p++;
			
			for(i = 0;i < 7; i++)
			{
				x += (*p - '0')*y;
				p++;
				y = y / 10.0;
			}
			
			mec_turn_du(&x);
			latitude = latitude + x;		//得到纬度
			p++;
			latitude_n = *p;				//得到纬度半球
			p++;
			p++;
			
			y = 100;
			for(i = 0;i < 3;i++)
			{
				longitude += (*p - '0') * y;
				p++;
				y = y / 10;
			}
			
			x = 0;
			y = 10;
			for(i = 0;i < 7; i++)
			{
				x += (*p - '0')*y;
				p++;
				y = y / 10.0;
			}
			p++;
			mec_turn_du(&x);
			longitude += x;
			longitude_n = *p;
			
			gps_data.latitude = latitude;
			gps_data.latitude_n = latitude_n;
			gps_data.longitude = longitude;
			gps_data.longitude_n = longitude_n;
		}
		
	}
	
}

void mec_turn_du(float *x)
{
	*x = *x / 60.0;
}