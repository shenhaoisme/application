#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
struct msgbuf{
	long mtype;
	int status;
	char time[20];
	char mtext[1024];
};

int main(int argc, char argv[])
{
	int msgid;
	struct msqid_ds info;
	struct msgbuf buf;
	int flag=-1;
	int reclen=0;
	int key;
	int mytype;
	
	msgid = msgget(0x11111111,0);
	if(msgid < 0)
	{
		printf("msgget fail\n");
		return -1;
	}
	reclen = sizeof(struct msgbuf) - sizeof(long);
	memset(&buf, 0, reclen);
	mytype=1;
	while(1)
	{
		flag = msgrcv(msgid, &buf, reclen, mytype, 0);
	
		if(flag < 0)
		{
			perror("recv message fail\n");
			return -1;
		}
	printf("type=%ld, time %s ,message %s\n", buf.mtype, buf.time, buf.mtext);	
	}	
	
	system("ipcs -q");
	return 0;
}

