#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
/*#define SERVPORT 4444		[>服务器监听端口号<]*/
/*#define SERVPORT 2001 //[>服务器监听端口号<]*/
#define SERVPORT 2000 //[>服务器监听端口号<]
#define MAXDATASIZE 256 	/*最大同时连接请求数*/
#define STDIN 0			 /*标准输入文件描述符*/

#define DEBUG

#ifdef DEBUG
#define pr_debug(x...) printf(x)
#else	
#define pr_debug(x...)
#endif

int main(void)
{
	FILE *fc_record,*fc_read;
	int sockfd;			/*套接字描述符*/
	int recvbytes;
	char buf[MAXDATASIZE];		/*用于处理输入的缓冲区*/
	char *str;
	
	char name[MAXDATASIZE];		/*定义用户名*/
	char send_str[MAXDATASIZE];	/*最多发出的字符不能超过MAXDATASIZE*/                   
	struct sockaddr_in serv_addr;		/*Internet套接字地址结构*/
	fd_set rfd_set, wfd_set, efd_set;/*被select()监视的读,写,异常处理的文件描述符集合*/  
	struct timeval timeout;/*本次select的超时结束时间*/
	int ret;				/*与server连接的结果*/

	char *wday[]={"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
	char ch;
	struct tm *p;
	time_t timep;
	int first=1;
	
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) { /*错误检测*/
		perror("socket");
		exit(1);
	}
	pr_debug("create socket %d\n", sockfd);
/* 填充 sockaddr结构  */
	bzero(&serv_addr, sizeof(struct sockaddr_in));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(SERVPORT);
    inet_aton("127.0.0.1", &serv_addr.sin_addr);
    /*inet_aton("127.0.0.2", &serv_addr.sin_addr);*/
    /*serv_addr.sin_addr.s_addr=inet_addr("192.168.0.101");*/

	pr_debug("connect %d\n", sockfd);
	if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr)) == -1) 
	{
		 /*错误检测*/
		perror("connect");
		exit(1);
	}
	pr_debug("connect %s:%d success %d\n", sockfd, serv_addr.sin_addr.s_addr, SERVPORT);

	fcntl(sockfd, F_SETFD, O_NONBLOCK);
	
	if((fc_record=fopen("c_record.txt","a+"))==NULL)	
		{		
			printf("can not open file c_record.txt,exit...\n");		
			return -1;	
		}
	
	printf("input your name:");
	
	scanf("%s",name);
	name[strlen(name)] = '\0';
	
	printf("%s: ",name);
		
	send(sockfd, name, strlen(name), 0);
/*发送用户名到sockfd*/	
	fprintf(fc_record,"%s: ",name);
	fflush(stdout);

while (1)
        {
		FD_ZERO(&rfd_set);/*将select()监视的读的文件描述符集合清除*/
		FD_ZERO(&wfd_set);/*将select()监视的写的文件描述符集合清除*/
		FD_ZERO(&efd_set);/*将select()监视的异常的文件描述符集合清除*/
		FD_SET(STDIN, &rfd_set);
/*将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
		FD_SET(sockfd, &rfd_set);
/*将新建的描述符加到seletct()监视的读的文件描述符集合中*/
		FD_SET(sockfd, &efd_set);
/*将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
		timeout.tv_sec = 10;/*select在被监视窗口等待的秒数*/
		timeout.tv_usec = 0;/*select在被监视窗口等待的微秒数*/
		ret = select(sockfd + 1, &rfd_set, &wfd_set, &efd_set, &timeout);
		if (ret == 0) {
			continue;
		}
		if (ret < 0) {
			perror("select error: ");
			exit(-1);
		}
/*判断是否已将标准输入文件描述符加到seletct()监视的读的文件描述符集合中*/
  		if (FD_ISSET(STDIN, &rfd_set))
		 {
			fgets(send_str, 256, stdin);
			send_str[strlen(send_str)-1] = '\0';
			if (strncmp("quit", send_str, 4) == 0) { /*退出程序*/
				close(sockfd);
				exit(0);
			}
			if (strcmp("record", send_str) == 0) {	  /*打开聊天记录*/
				if((fc_read=fopen("c_record.txt","r"))==NULL)	
				{		
					printf("can not open file c_record.txt,exit...\n");		
					return -1;	
				}
				putchar('\t');
				while(!feof(fc_read)){
						ch=fgetc(fc_read);
						putchar(ch);
                  if(ch=='\n')						               	  
						  putchar('\t');
				}						                                               
				fclose(fc_read);
				printf("\n%s: ",name);
				fflush(stdout);
				continue;
			}
			
			time(&timep);
			p=localtime(&timep);		
			send(sockfd, send_str, strlen(send_str), 0);
			printf("        ( %d年%d月%2d日  ", (1900+p->tm_year),(1+p->tm_mon),p->tm_mday);   			
			printf("%s %2d:%2d:%2d )\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);	  
			fprintf(fc_record,"%s\n",send_str);
			fprintf(fc_record,"        ( %d年%d月%2d日  ",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
			fprintf(fc_record,"%s %2d:%2d:%2d )\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);
		}
/*判断是否已将新建的描述符加到seletct()监视的读的文件描述符集合中*/
		if (FD_ISSET(sockfd, &rfd_set)) 
		{
			recvbytes=recv(sockfd, buf, MAXDATASIZE, 0);
			if (recvbytes == 0) 
			{
				close(sockfd);
				exit(0);
			}
			buf[recvbytes] = '\0';
			time(&timep);
			p=localtime(&timep);
			printf("Server: %s\n", buf);
			
         printf("        ( %d年%d月%2d日  ",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
			printf("%s %2d:%2d:%2d )\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec); 

			fprintf(fc_record,"Server:%s\n",buf);
         fprintf(fc_record,"        ( %d年%d月%2d日  ",(1900+p->tm_year),(1+p->tm_mon),p->tm_mday);
			fprintf(fc_record,"%s %2d:%2d:%2d )\n",wday[p->tm_wday],p->tm_hour,p->tm_min,p->tm_sec);
			fprintf(fc_record,"%s: ",name);
			
			printf("%s: ",name);
			fflush(stdout);
		}
/*判断是否已将新建的描述符加到seletct()监视的异常的文件描述符集合中*/
		if (FD_ISSET(sockfd, &efd_set))
		 {
			close(sockfd);
			exit(0);
		}
	}
}
