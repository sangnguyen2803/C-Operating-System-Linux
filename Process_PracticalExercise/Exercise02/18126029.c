#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



int main()
{
	char buff[100];
	int pip1[2];
	int pip2[2];
	pipe(pip1);
	pipe(pip2);
	int n;
	int pid = fork();
	
	if(pid < 0){
		perror("Child process is not created");
		exit(0);
	}
	if(pid > 0){
		printf("P - Enter a message (1 word): ");
		scanf("%s", buff);
		close(pip1[0]);
		close(pip2[1]);
		write(pip1[1],buff,100);
		n = read(pip2[0], buff, 100);
		printf("P - The message received from child process is: %s\n",buff);
	}
	else if(pid == 0){
		close(pip1[1]);
		close(pip2[0]);
		n = read(pip1[0], buff, 100);
		printf("C - The message received from parent process is: %s\n",buff);
		for(int i = 0; i < strlen(buff); i++){
			if(buff[i] <= 'z' && buff[i] >= 'a')
				buff[i]-= 32;	
		}
		write(pip2[1],buff, 100);
	}	
	return 0;
}
