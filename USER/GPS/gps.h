#ifndef __GPS_H
#define __GPS_H

typedef struct
{
	float longitude;		//����
	char longitude_n;
	float latitude;		//γ��
	char latitude_n;
	
}GPS_DATA;

void gps_start();
void gps_getdata();
void Gps_Gpgll_Process();
void mec_turn_du(float *x);
#endif