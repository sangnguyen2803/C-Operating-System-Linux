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
    	int fNum, sNum, result, operator;
    	printf( "server waiting...\n" );
    	client_sockfd = accept( server_sockfd, (struct sockaddr*)&client_address, &client_len );
    	while (1){
    		write(client_sockfd, "Enter-first-number: ", 100);
    		read(client_sockfd, &fNum, sizeof(int));
    		printf("- Client - first number: %d", fNum);
    		printf("\n");
    		
    		write(client_sockfd, "Enter-second-number: ", 100);
    		read(client_sockfd, &sNum, sizeof(int));
    		printf("- Client - second number: %d", sNum);
    		printf("\n");
    		
    		write(client_sockfd, "Choose one of the operators: \n1: Add(+) \n2: Substract(-) \n3: Multiply(*)\n4: Devide(/)\nYour choice: ", 200);
    		read(client_sockfd, &operator, sizeof(int));
    		printf("- Client selection: %d", operator);
    		printf("\n");
    		
    		switch(operator)
    		{
    			case 1:
    				result = fNum + sNum;
    				break;
    			case 2:
    				result = fNum - sNum;
    				break;
    			case 3:
    				result = fNum * sNum;
    				break;
    			case 4:
    				result = fNum / sNum;
    				break;
    		}
    		write(client_sockfd, &result, sizeof(int));
    	}
    	close( client_sockfd );
  	}
  return 1;
}
