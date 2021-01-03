#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *tieutrinh( void *arg );

int main()
{
	pthread_t thread1, thread2;
	char *message1 = "18126029";
	char *message2 = "Nguyen Sang";
	int iret1;
	int iret2;
	void *result;
	
	iret1 = pthread_create( &thread1, NULL, tieutrinh, (void*) message1);
	
	iret2 = pthread_create( &thread2, NULL, tieutrinh, (void*) message2);
	
	printf("pthread_create() for thread 1 returns: %d\n",iret1);
	printf("pthread_create() for thread 2 returns: %d\n",iret2);
	pthread_join( thread1,&result);
	printf("Tien trinh cha: %s \n",(char*)result);
	pthread_join( thread2,&result);
	printf("%s", (char*)result);
	exit(EXIT_SUCCESS);
}

void *tieutrinh( void *arg){
	char *message;
	message = (char *) arg;
	printf("%s \n", message);
	return message;
}

