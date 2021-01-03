#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main()
{
  	int server_sockfd, client_sockfd;
  	int server_len, client_len;
  	struct sockaddr_un server_address;
  	struct sockaddr_un client_address;
  	
	unlink( "server_socket" );
  
  	server_sockfd = socket( AF_UNIX, SOCK_STREAM, 0 );
  	server_address.sun_family = AF_UNIX;
  	strcpy( server_address.sun_path, "server_socket" );
  	server_len = sizeof( server_address );
  
  	bind( server_sockfd, (struct sockaddr *)&server_address, server_len );
  
  	listen( server_sockfd, 5 );
    while ( 1 ){
    	char message1[50];
    	char message2[50];
    	printf( "server waiting...\n" );
    	client_sockfd = accept( server_sockfd, (struct sockaddr*)&client_address, &client_len );
    	while (1){
    		printf("- Server message: ");
    		scanf("%s",message1);
    		write(client_sockfd, &message1, 50);
    		read(client_sockfd, &message2, 50);
    		printf("+++ Client: ");
    		printf("%s",message2);
    		printf("\n");
    	}
    	close( client_sockfd );
  	}
  return 1;
}


