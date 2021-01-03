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
  char message3[200];
  int fNum, sNum;
  int choice;
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
    	read (sockfd, &message1,100);
    	printf("%s",message1);
    	scanf("%d",&fNum);
    	write( sockfd, &fNum, sizeof(int));
    	
    	read (sockfd, &message2,100);
    	printf("%s",message2);
    	scanf("%d",&sNum);
    	write( sockfd, &sNum, sizeof(int));
    	
    	read (sockfd, &message3,200);
    	printf("%s", message3);
    	scanf("%d",&choice);
    	write( sockfd, &choice, sizeof(int));
    	
    	read (sockfd, &result, 10);
    	printf("-Client - Result calculated from server is %d \n",result);
  }
  close( sockfd );
  return 1;
}

