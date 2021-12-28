// C Program for Message Queue (Writer Process)
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#include<unistd.h>
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

	// ftok to generate unique key
	key = ftok("msf1", 65);
	key2 = ftok("msf2", 66);
	
	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgid2 = msgget(key2, 0666 | IPC_CREAT);
	msgctl(msgid, IPC_RMID, NULL);
	
	msgctl(msgid2, IPC_RMID,NULL);
	printf("Cleared\n");
	
	// ftok to generate unique key
	key = ftok("msf1", 65);
	key2 = ftok("msf2", 66);
	
	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgid2 = msgget(key2, 0666 | IPC_CREAT);
	
	message.mesg_type=1;
	while(1)
	{
	printf("Write Data : ");
	fgets(message.mesg_text,MAX,stdin);
	//gets(message.mesg_text);
	
	// msgsnd to send message
	for(int i=0;i<4;i++) {
		message.mesg_type=i+1;
		msgsnd(msgid, &message, sizeof(message), 0);
	}
	
	if(strcmp(message.mesg_text,"end\n")==0)
	break;
	printf("Data sent is : %s", message.mesg_text);
	int count=0;
	while(count<4)
	{
	count+=1;
	//printf("Waiting for query\n");
	msgrcv(msgid2, &query, sizeof(query),count, 0);
	printf("Query from Farmer %ld is : %s", query.sender,query.mesg_text);
	
	sleep(1);	
	}
	
	}
	return 0;
}

