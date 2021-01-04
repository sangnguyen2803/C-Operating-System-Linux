#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int nb_male = 0, nb_female = 0;
int femaleSwitch = 0, maleSwitch = 0;

sem_t empty, maleMultiplex, femaleMultiplex, mutex_woman, mutex_man, empty_woman, empty_man, random_personne;

int Light_Switch()
{	
	sem_wait(&empty);
	return 1;
}

void* woman_bathroom(void *ID)
{
	sem_wait(&random_personne);
	sem_wait(&empty_woman);
	sem_wait(&mutex_woman);
	
	nb_female++;
	if(nb_female == 1)
	{
		femaleSwitch = Light_Switch();	
		sem_wait(&empty_man);
	}
	sem_post(&mutex_woman);
	sem_post(&empty_woman);
	sem_post(&random_personne);
	
	sem_wait(&maleMultiplex);
	printf("%s enter in the room\n", (char*)ID);

	sem_post(&maleMultiplex);
	printf("%s leave the room\n", (char*)ID);


	
	sem_wait(&mutex_woman);
	nb_female--;
	if(nb_female == 0 && femaleSwitch == 1)
	{
		femaleSwitch = 0;
		sem_post(&empty);
		sem_post(&empty_man);
	
	}
	sem_post(&mutex_woman);
}


void* man_bathroom(void *ID)
{
	sem_wait(&random_personne);
	sem_wait(&empty_man);
	sem_wait(&mutex_man);	
	nb_male++;
	if(nb_male == 1)
	{
		maleSwitch = Light_Switch();
		sem_wait(&empty_woman);	
	}
	sem_post(&mutex_man);
	sem_post(&empty_man);
	sem_post(&random_personne);

	sem_wait(&maleMultiplex);
	printf("%s enter in the room\n", (char*)ID);
	sem_post(&maleMultiplex);
	printf("%s leave the room\n", (char*)ID);
	
	sem_wait(&mutex_man);
	nb_male--;

	if(nb_male == 0 && maleSwitch == 1)
	{
		maleSwitch = 0;
		sem_post(&empty);
		sem_post(&empty_woman);
	}
	sem_post(&mutex_man);
}

int main()
{

	sem_init(&empty, 0, 1);
	sem_init(&empty_woman, 0, 1);
	sem_init(&empty_man, 0, 1);
	sem_init(&random_personne, 0, 1);
	sem_init(&mutex_woman, 0, 1);
	sem_init(&mutex_man, 0, 1);
	sem_init(&maleMultiplex, 0, 3);
	sem_init(&femaleMultiplex, 0, 3);
	char* woman1 = "Woman_1";
	char* man1 = "Man_1";
	char* woman2 = "Woman_2";
	char* man2 = "Man_2";
	char* woman3 = "Woman_3";
	char* man3 = "Man_3";
	char* woman4 = "Woman_4";
	char* man4 = "Man_4";
	char* woman5 = "Woman_5";
	char* man5 = "Man_5";
	char* woman6 = "Woman_6";
	char* man6 = "Man_6";
	char* woman7 = "Woman_7";
	char* man7 = "Man_7";
	char* woman8 = "Woman_8";
	char* man8 = "Man_8";	
	pthread_t pth1, pth2, pth3, pth4, pth5, pth6, pth7, pth8, pth9, pth10, pth11
	,pth12, pth13, pth14, pth15, pth16;// this is our thread identifier
	
	pthread_create(&pth1,NULL,woman_bathroom,(void*)woman1);
	pthread_create(&pth2,NULL,man_bathroom,(void*)man1);
	pthread_create(&pth3,NULL,man_bathroom,(void*)man2);
	pthread_create(&pth4,NULL,woman_bathroom,(void*)woman2);
	pthread_create(&pth5,NULL,woman_bathroom,(void*)woman3);
	pthread_create(&pth6,NULL,man_bathroom,(void*)man3);
	pthread_create(&pth7,NULL,woman_bathroom,(void*)woman4);
	pthread_create(&pth8,NULL,man_bathroom,(void*)man4);
	pthread_create(&pth9,NULL,woman_bathroom,(void*)woman5);
	pthread_create(&pth10,NULL,man_bathroom,(void*)man5);
	pthread_create(&pth11,NULL,woman_bathroom,(void*)woman6);
	pthread_create(&pth12,NULL,man_bathroom,(void*)man6);
	pthread_create(&pth13,NULL,woman_bathroom,(void*)woman7);
	pthread_create(&pth14,NULL,man_bathroom,(void*)man7);
	pthread_create(&pth15,NULL,woman_bathroom,(void*)woman8);
	pthread_create(&pth16,NULL,man_bathroom,(void*)man8);
	pthread_join(pth1,NULL);
	pthread_join(pth2,NULL);
	pthread_join(pth3,NULL);
	pthread_join(pth4,NULL);
	pthread_join(pth5,NULL);
	pthread_join(pth6,NULL);
	pthread_join(pth7,NULL);
	pthread_join(pth8,NULL);
	pthread_join(pth9,NULL);
	pthread_join(pth10,NULL);
	pthread_join(pth11,NULL);
	pthread_join(pth12,NULL);
	pthread_join(pth13,NULL);
	pthread_join(pth14,NULL);
	pthread_join(pth15,NULL);
	pthread_join(pth16,NULL);
	return 0;	
}
