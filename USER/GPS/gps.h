#ifndef __GPS_H
#define __GPS_H

typedef struct
{
	float longitude;		//¾­¶È
	char longitude_n;
	float latitude;		//Î³¶È
	char latitude_n;
	
}GPS_DATA;

void gps_start();
void gps_getdata();
void Gps_Gpgll_Process();
void mec_turn_du(float *x);
#endif