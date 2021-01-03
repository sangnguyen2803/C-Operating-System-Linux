#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

int main()
{
  int sockfd;				/* s? mô t? socket - socket handle */
  int len;
  struct sockaddr_un address;		/* structure quan tr?ng, ch?a các thông tin v? socket */
  int result;
  char message1[50];
  char message2[50];
  char a[10],b[10];
  int option;
  sockfd = socket( AF_UNIX, SOCK_STREAM, 0 );
  address.sun_family = AF_UNIX;
  strcpy( address.sun_path, "server_socket" );
  len = sizeof( address );
  
  result = connect( sockfd, (struct sockaddr*)&address, len );
  if ( result == -1 ) { 
    perror( "Oops: client1 problem" );
    return 1;
  }
  while(1)
  {
    	read ( sockfd, &message2, 50 );
  	printf("+++Server: ");
    	printf("%s",message2);
    	printf("\n");
    	printf("- Client message: ");
    	scanf("%s",message1);
  	write( sockfd, &message1, 50 );
  }
  close( sockfd );
  return 1;
}

