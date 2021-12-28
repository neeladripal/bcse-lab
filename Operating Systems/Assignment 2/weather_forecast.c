#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#define BUFFER_SIZE 200

int main(){
	int pipefds[4][2];
	for(int i=0;i<4;i++) {
		int retst = pipe(pipefds[i]);
		if(retst== -1){
			perror("Pipe creation failed");
			exit(1);
		}
	}
	
	pid_t pid = fork();
	
	if(pid < 0){
		perror("Child process creation failed");
		exit(1);
	}

	// child process
	else if(pid == 0) {
		for(int i=0;i<4;i++)
			close(pipefds[i][1]); // close writing end of pipe
		
		int recid=1;
		pid_t pid2=fork();
		
		if(pid2==0)
			recid=2;

		int pr = recid;
		pid_t pid3=fork();

		if(pid3==0) {
			if(pr==1)
			recid=3;
			else
			recid=4;
		}

		char str[BUFFER_SIZE];
		while(1) {
			if(read(pipefds[recid-1][0],&str,BUFFER_SIZE) > 0){
				if(strcmp(str,"end")==0)
					break;
				printf("Listener %d -> Weather report received : %s",recid,str);
			}
		}
		close(pipefds[recid-1][0]); // close reading end of pipe
		exit(0);
	}
	
	// parent process
	else if(pid > 0) {
		printf("\n\n---------------------- BROADCASTING STARTS -----------------------\n\n\n");
		
		for(int i=0;i<4;i++)
		close(pipefds[i][0]); // close reading end of pipe
		
		char str[BUFFER_SIZE];
		FILE *fp = fopen("wreport.txt", "r");
		if (fp == NULL) {
        	printf("Error: could not open file \n" );
        	return 1;
    	}
    		
		while(fgets ( str, 200, fp )) {
			printf("Weather condition to be broadcasted : %s",str);
			for(int i=0;i<4;i++)
				write(pipefds[i][1],str,BUFFER_SIZE);
			sleep(1);
		}
		for(int i=0;i<4;i++)
			write(pipefds[i][1],"end\0",BUFFER_SIZE);
			
		//wait(NULL);// wait till end of reader process
		sleep(1);
		printf("\n\n\n----------------------END OF BROADCASTING-----------------------\n");
		for(int i=0;i<4;i++)
			close(pipefds[i][1]);//close writing end of pipe
	}
	return 0;
}
