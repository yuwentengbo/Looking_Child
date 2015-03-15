#include "ebook.h"
#include "exfuns.h"
#include "ff.h"
#include "usart.h"
#include "string.h"
#include "key.h"
#include "delay.h"
#include "lcd.h"
#include "fontupd.h"
#include "text.h"


char *filename[10];			//带路径
char *filename1[10];		//名字
u8 fileindex = 0;
u8 select_index = 0;
u8 filecont[600];

void ebook_init()
{
	if(exfuns_init() == 1)
	{
		printf("%s","文件系统申请内存失败");
		return ;
	}
	f_mount(fs[0],"0:",1);   //挂载SD卡
}

void ebook_start()
{
	ebook_read_filename();
	ebook_showbooknames();
	ebook_chose();

}
void ebook_chose()
{
	u8 key_value = 0;
	while(key_value == 0)
	{
		key_value = KEY_Scan(0);
		delay_ms(10);
		switch(key_value)
		{
			case KEY0_PRES:
				select_index = select_index + 1;
				select_index = select_index % fileindex;
				ebook_showbooknames();
				break;
			case KEY1_PRES:
				ebook_read_file(select_index);
				break;
			case WKUP_PRES:
				return;
		}
	}
}

void ebook_showbooknames()
{
	u8 i,y = 30;
	POINT_COLOR = BLUE;
	for(i=0;i<fileindex;i++)
	{
		LCD_ShowNum(20,y,i+1,1,16);
		Show_Str(25,y,200,20,(u8 *)filename1[i],16,0);
		y = y + 30;
	}
	POINT_COLOR = RED;
	LCD_ShowChar(20,y*(select_index + 1),'_',16,0);
	POINT_COLOR = BLACK;
}

void ebook_read_filename()
{
	char* path,path1;       /* Start node to be scanned (also used as work area) */
	FRESULT res;
    FILINFO fno;
    DIR dir;
    int i;
    char *fn;   	/* This function assumes non-Unicode configuration */
	static char lfn[_MAX_LFN + 1];   /* Buffer to store the LFN */
    fno.lfname = lfn;
    fno.lfsize = sizeof lfn;
	
	path = "0:/EBOOK";
	res = f_opendir(&dir, path);                       /* Open the directory */
    if (res == FR_OK) 
	{
        for (;;) 
		{
            res = f_readdir(&dir, &fno);                   /* Read a directory item */
            if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
            if (fno.fname[0] == '.') continue;             /* Ignore dot entry */

            fn = *fno.lfname ? fno.lfname : fno.fname;

            fn = fno.fname;
            if (fno.fattrib & AM_DIR) 
			{                    /* It is a directory */
                sprintf(&path[i], "/%s", fn);
                path[i] = 0;
                if (res != FR_OK) break;
            } 
			else 
			{                                       /* It is a file. */
				printf("%s/%s\n", path, fn);
				strcpy(filename1[fileindex],fn); 
				strcat(path,"/");
				strcat(path,fn);
				strcpy(filename[fileindex++],path);
			}
        }
        f_closedir(&dir);
    }

}

void ebook_read_file(u8 index)
{
	static u8 ye_index = 1,ye_max = 0;
	static DWORD i = 0;
	u8 key_value = 0;
	u32 size = 0;
	UINT  fr = 0,br = 1;
	if(FR_OK ==f_open(file,filename[index], FA_READ))
	{
		size = file->fsize;
		ye_max = size / 600;
		ye_max = ye_max + 1;
		f_read(file,filecont,600,&br);		 /* Read a chunk of source file */
		ebook_showcont();
		i = i + 600;
		while(1)
		{
			while(key_value == 0)
			{
				key_value = KEY_Scan(0);
				delay_ms(10);
			}
			switch(key_value)
			{
				case KEY0_PRES:
					if(ye_index == 1)
					{
						Show_Str(120,300,100,20,"已是首页",16,0);//显示一是首页
						break;
					}
					else
					{
						i = i - 600;
						f_lseek(file,i);
					}
					break;
				case KEY1_PRES:
					if(ye_index > ye_max)
					{
						Show_Str(120,300,100,20,"已是末页",16,0);//显示一是末页
						break;
					}
					else
					{
						i = i + 600;
					}
					break;
				case WKUP_PRES:
					return;
					break;
			}
			f_read(file,filecont,600,&br);		 /* Read a chunk of source file */
			if (fr || br == 0) 	break; 			 /* error or eof */
			ebook_showcont();
		}
		f_close(file);
    }
    else
	{
		printf("%s","文件打开失败");
	}
}

void ebook_showcont()
{
	u8 i,*p;
	p = filecont;
	POINT_COLOR = BLACK;
	for(i = 0; i < 20;i++)
	{
		Show_Str(0,i*16,240,16,p,16,0);
	}
}