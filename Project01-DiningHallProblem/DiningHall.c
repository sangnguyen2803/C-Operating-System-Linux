#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t mutex;
sem_t okToLeave;

int eating = 0;
int readyToLeave = 0;

void getFood(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);	
	printf("got food\n");
}

void dine(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);
	printf("is dining\n");
	if(arg == "Student 3")
		usleep(5000);
	if(arg == "Student 4")
	if(arg == "Student 2")
		usleep(1000);
}

void finishDining(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);
	printf("has just done dining\n");
}

void leave(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);	
	printf("left\n");
}

void waiting1(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);	
	printf("is waiting for other friends to finish dining\n");
}

void waiting2(void *arg){
	char *message;
	message = (char *) arg;
	printf("%s ",message);	
	printf("finds that there is nobody in the dining hall, so he leaves\n");
}



void *diningHall(void *arg){
	getFood(arg);
	sem_wait(&mutex);
	eating++;
	if( eating == 2 && readyToLeave == 1){
		sem_post(&okToLeave);
		readyToLeave--;
	}
	sem_post(&mutex);
	dine(arg);
	sem_wait(&mutex);
	
	eating--;
	finishDining(arg);
	readyToLeave++;
	
	if( eating == 1 && readyToLeave == 1 ){
		sem_post(&mutex);
		waiting1(arg);
		sem_wait(&okToLeave);
	}
	else if ( eating == 0 && readyToLeave == 2){
		sem_post(&okToLeave);
		readyToLeave -= 2;
		waiting2(arg);
		sem_post(&mutex);
	}
	else{
		readyToLeave--;
		sem_post(&mutex);
	}
	
	usleep(1);
	leave(arg);
	return NULL;
}


int main(void){
	sem_init(&mutex, 0, 1);
	sem_init(&okToLeave, 0, 0);
	pthread_t pth1, pth2, pth3, pth4, pth5, pth6, pth7, pth8, pth9;
	
	char *student1 = "Student 1";
	char *student2 = "Student 2";
	char *student3 = "Student 3";
	char *student4 = "Student 4";
	char *student5 = "Student 5";
	char *student6 = "Student 6";
	char *student7 = "Student 7";
	char *student8 = "Student 8";
	char *student9 = "Student 9";
	
	pthread_create(&pth1,NULL,diningHall, (void*)student1);
	pthread_create(&pth2,NULL,diningHall, (void*)student2);
	pthread_create(&pth3,NULL,diningHall, (void*)student3);
	pthread_create(&pth4,NULL,diningHall, (void*)student4);
	pthread_create(&pth5,NULL,diningHall, (void*)student5);
	pthread_create(&pth6,NULL,diningHall, (void*)student6);
	pthread_create(&pth7,NULL,diningHall, (void*)student7);
	pthread_create(&pth8,NULL,diningHall, (void*)student8);
	pthread_create(&pth9,NULL,diningHall, (void*)student9);

	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);
	pthread_join(pth3,NULL);
	pthread_join(pth4,NULL);
	pthread_join(pth5,NULL);
	pthread_join(pth6,NULL);
	pthread_join(pth7,NULL);
	pthread_join(pth8,NULL);
	pthread_join(pth9,NULL);

	sem_destroy(&mutex);
	sem_destroy(&okToLeave);
	
	return 0;
}
