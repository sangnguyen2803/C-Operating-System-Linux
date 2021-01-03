#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



sem_t mutex;
int lock = 0;

void *threadFunc(void *arg){
	char c;
	FILE *f;
	sem_wait(&mutex);
	f = fopen("text.txt","w");
	if(f)
	{
		fseek(f, 0, SEEK_END);
		int length = ftell(f);
		if( length == 0 ){
			fprintf(f,"18126029 - Nguyen Sang\n");
			sem_post(&mutex);
		}
		fclose(f);
	}
	
	f = fopen("text.txt","r");
	sem_wait(&mutex);
	usleep(1);
	if(f && lock == 0)
	{
		while((c = getc(f)) != EOF){
			putchar(c);
		}
		fclose(f);
		lock++;
	}
	sem_post(&mutex);
	return NULL;
}

int main(void){
	sem_init(&mutex,0, 1);
	pthread_t pth1, pth2; //thread identifier
	pthread_create(&pth1,NULL,threadFunc,NULL);
	pthread_create(&pth2,NULL,threadFunc,NULL);
	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);
	sem_destroy(&mutex);
	return 0;
}
