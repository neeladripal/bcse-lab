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
		pid_t pid2=fork();
		if(pid2==0)
		recid=2;
		int pr=recid;
		pid_t pid3=fork();
		if(pid3==0)
		{
		if(pr==1)
		recid=3;
		else
		recid=4;
		}
	// ftok to generate unique key
	//printf("He\n");
	//int (*qst)[5];
	//for(int i=0;i<5;i++)
	//(*qst)[i]=0;
	//printf("He2\n");
	//*qst[0]=0;
	int ps=0;
	// ftok to generate unique key
	key = ftok("msf1", 65);
	key2 = ftok("msf2", 66);
	//printf("%d\n",recid);
	// msgget creates a message queue
	// and returns identifier
	msgid = msgget(key, 0666 | IPC_CREAT);
	msgid2 = msgget(key2, 0666 | IPC_CREAT);
	while(1)
	{
	//(*qst)[0]++;
	// msgrcv to receive message
	
	msgrcv(msgid, &message, sizeof(message), recid, 0);
	if(recid==1)
	{
		FILE *fptr ; 

		fptr = fopen("temp.txt", "w");

		fprintf(fptr, "%d",0);
		fclose(fptr);
	}
	if(strcmp(message.mesg_text,"end\n")==0)
	break;
	// display the message
	printf("Farmer %d -> Data Received is : %s",recid,
					message.mesg_text);
	ps+=1;
	//printf("%d %d\n",ps,(*qst)[recid-1]);
	sleep(1);
	//printf("%d\n",recid);
	while(1)
	{
		FILE *fptr ; 
		fptr = fopen("temp.txt", "r");
		int c=-2;
		fscanf(fptr, "%d",&c);
		//printf("%d\n",c);
		fclose(fptr);
		if(c==recid-1)
		break;
	}
	//while((*qst)[recid-1]!=ps){printf("%d",recid);sleep(1);}
	//(*qst)[recid]+=1;printf("%d %d\n",recid,(*qst)[recid]);
	sleep(1);
	printf("Farmer Head %d -> Write Query : ",recid);
	fgets(query.mesg_text,MAX,stdin);
	//scanf("%s",query.mesg_text);
	//gets(query.mesg_text);
	query.sender=recid;
	msgsnd(msgid2, &query, sizeof(query), 0);
	//while(qst[4]!=ps){}
	FILE *fptr ; 


		fptr = fopen("temp.txt","w");
		fprintf(fptr, "%d",recid);
		fclose(fptr);
	}
	// to destroy the message queue
	msgctl(msgid, IPC_RMID, NULL);
	msgctl(msgid2, IPC_RMID,NULL);

	return 0;
}

