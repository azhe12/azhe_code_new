#include  <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	
	int client_sockfd = 0,test_sockfd=0;
	int len;
	struct sockaddr_un server_sockaddr,cli_sockaddr,test_sockaddr;
	int result;
	char dst_module_id='B';
	char ch='1';
	char src_module_id;
	
	
	client_sockfd= socket(AF_UNIX,SOCK_STREAM,0);
	printf("azhe:ClientA: client_sockfd=%d\n", client_sockfd);
	
	
//	memset( &cli_sockaddr, 0, sizeof( cli_sockaddr) ) ;
	cli_sockaddr.sun_family = AF_UNIX ;
	strcpy( cli_sockaddr.sun_path, "A" ) ;
	bind( client_sockfd, ( struct sockaddr * )&cli_sockaddr, sizeof( cli_sockaddr ) ) ;
#if 0
	printf("ls \n\n");	
	sleep(10);
#endif
	server_sockaddr.sun_family=AF_UNIX;
//	server_sockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
//	server_sockaddr.sin_port=htons(9734);
	strcpy( server_sockaddr.sun_path, "server_socket" ) ;
	len=sizeof(server_sockaddr);
	
	result = connect(client_sockfd,( struct sockaddr * )&server_sockaddr,len);
	if (result <0){
		printf("ClientA::error on connecting \n");	
//		exit(1);
	}
#if 0
	test_sockfd= socket(AF_UNIX,SOCK_STREAM,0);
	
	
//	memset( &cli_sockaddr, 0, sizeof( cli_sockaddr) ) ;
	test_sockaddr.sun_family = AF_UNIX ;
	strcpy( test_sockaddr.sun_path, "test" ) ;
	bind( test_sockfd, ( struct sockaddr * )&test_sockaddr, sizeof( test_sockaddr ) ) ;
#endif	

	printf("ClientA::succeed in connecting with server, client_sockfd=%d, test_sockfd=%d\n", client_sockfd,test_sockfd);
	sleep(10);
	write(client_sockfd,&dst_module_id,1);
	write(client_sockfd,&ch,1); 
	read (client_sockfd,&src_module_id,1); 
	read (client_sockfd,&ch,1); 
	printf("ClientA::char from  Client %c =%c\n", src_module_id,ch);	
	close (client_sockfd);
	
}	