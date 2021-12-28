// C Program for Message Queue (Reader Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <string.h>
#include<unistd.h>
#include <sys/msg.h>
#define MAX 100

// structure for message queue
struct mesg_buffer {
	long mesg_type;
	char mesg_text[100];
} message;

struct query_buffer {
	long sender;
	char mesg_text[100];
} query;

int main()
{
	key_t key,key2;
	int msgid,msgid2;
	int recid=1;

	// create 4 listener processes with ith listener having recid = i
	pid_t pid2 = fork();
	if (pid2==0)
		recid=2;
	int pr=recid;	
	pid_t pid3=fork();
	if(pid3==0) {
		if(pr==1)
			recid=3;
		else
			recid=4;
	}

	// generate unique key
	key = ftok("mesfl", 75);
	key2 = ftok("msf2", 76);
	
	// msgget creates a message queue and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgid2 = msgget(key2, 0666 | IPC_CREAT);
	
	while(1) {
		// msgrcv to receive message
		msgrcv(msgid, &message, sizeof(message), recid, 0);

		// if it is the listener with id 1, write 0 in file
		if(recid==1) {
			FILE *fptr;
			fptr = fopen("temp.txt", "w");
			fprintf(fptr, "%d", 0);
			fclose(fptr);
		}

		// if the received message is end, terminate
		if(strcmp(message.mesg_text,"end\n")==0)
			break;

		// display the message
		printf("Farmer %d -> Message from broadcaster: %s", recid, message.mesg_text);
		sleep(1);

		while(1) {
			FILE *fptr ; 
			fptr = fopen("temp.txt", "r");
			int c=-2;

			// read the id of the last listener
			fscanf(fptr, "%d", &c);
			fclose(fptr);

			// if the last listener has already received the message
			if(c == recid-1)
				break;
		}

		sleep(1);

		// get the message from the farmer
		printf("Farmer %d -> Write Query : ", recid);
		// scanf(" %s", query.mesg_text);
		fgets(query.mesg_text,MAX,stdin);
		
		// set the message type of listener
		query.sender=recid;
		
		// send the message
		msgsnd(msgid2, &query, sizeof(query), 0);
		
		// store the id in file
		FILE *fptr ; 
		fptr = fopen("temp.txt","w");
		fprintf(fptr, "%d",recid);
		fclose(fptr);
	}

	// destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	msgctl(msgid2, IPC_RMID,NULL);

	return 0;
}

