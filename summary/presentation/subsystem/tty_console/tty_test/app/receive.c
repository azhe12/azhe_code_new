#include <stdio.h>  
#include <string.h>  
#include <malloc.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <termios.h>  
#include "math.h"  
#define max_buffer_size 100 /*定义缓冲区最大宽度*/  
/*********************************************************/  
int fd, s;  
int open_serial(int k)  
{  
    if(k==0) /*tty设备选择*/  
    {  
        fd = open("/dev/ttty_azhe0",O_RDWR|O_NOCTTY); /*读写方式打开设备*/  
        perror("open /dev/ttty_azhe0\n");  
    }  
    else  
    {  
        fd = open("/dev/ttty_azhe1",O_RDWR|O_NOCTTY);  
        perror("open /dev/ttty_azhe1");  
    }  
    if(fd == -1) /*打开失败*/  
        return -1;  
    else  
        return 0;  
}  
/********************************************************************/  
int main()  
{  
    char hd[max_buffer_size],*rbuf; /*定义接收缓冲区*/  
    int flag_close, retv,i,ncount=0;  
    struct termios opt;  
/*******************************************************************/  
    open_serial(0); /*打开设备0*/  
/*******************************************************************/  
    tcgetattr(fd,&opt);  
    cfmakeraw(&opt);  
/*****************************************************************/  
    //cfsetispeed(&opt,B9600); /*波特率设置为9600bps*/  
     //cfsetospeed(&opt,B9600);  
/*******************************************************************/  
    tcsetattr(fd,TCSANOW,&opt);  
    rbuf=hd; /*数据保存*/  
    printf("ready for receiving data...\n");  
    retv=read(fd,rbuf,1); /*接收数据*/  
    if(retv==-1)  
    {  
        perror("read"); /*读状态标志判断*/  
    }  
/*************************开始接收数据******************************/  
    /*判断数据是否接收完毕*/
    while( *rbuf!='\n')
    {  
        ncount+=1;  
        rbuf++;  
        retv=read(fd,rbuf,1);  
        if(retv==-1)  
        {  
            perror("read\n");  
        }  
    }  
/*******************************************************************/  
    printf("The data received is:\n"); /*输出接收到的数据*/  
    for(i=0;i<ncount;i++)  
    {  
        printf("%c",hd[i]);  
    }  
    printf("\n");  
    flag_close =close(fd);  
    if(flag_close == -1) /*判断是否成功关闭文件*/  
        printf("Close the Device failur！\n");  
    return 0;  
}  
