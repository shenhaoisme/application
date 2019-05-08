#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define TEXT_SIZE 512

struct msgbuf
{
	long mtype;
	int status;
	char time[20];
	char mtext[TEXT_SIZE];
};

char *get_local_time()
{
	time_t tv;
	static char buf[20];
	struct tm *tmp;
	tv = time(0); //
	tmp = localtime(&tv);
	sprintf(buf, "%02d:%02d:%02d",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
	return buf;
}

int main(int argc, char * argv[])
{
	int msgid; //queue ID
	struct msgbuf buf;
	struct msqid_ds info; 
	struct msgbuf buf2;
	
	int flag =-1;
	int sndlen, reclen;
	int key;
	
	key = ftok("msg.tmp", 0x01);
	if(key < 0)
	{
		perror("fotk fail \n");
		return -1;
	}
	/*IPC_CREAT：当msgflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列，返回此消息队列的标识符

IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错

	*/
	msgid = msgget(key, 0600|IPC_CREAT); 
	if(msgid < 0)
	{
		perror("create msg queue error\n");
		return -1;
	}
	buf.mtype =1;
	buf.status = 9;
	strcpy(buf.time, get_local_time());
	strcpy(buf.mtext,"shenhao : hello world");
	sndlen = sizeof(struct msgbuf) - sizeof(long);
	flag = msgsnd(msgid, &buf, sndlen, 0); // 0 ?
	if (flag < 0)
	{
		perror("msg send fail\n");
		return -1;
	}
	sleep(2);
	buf.mtype =  3;
	buf.status = 9;
	strcpy(buf.time, get_local_time());
	strcpy(buf.mtext,"shenhao : bye bye");
	sndlen = sizeof(struct msgbuf) - sizeof(long);
	flag = msgsnd(msgid, &buf2, sndlen, 0); // 0 ?
	if (flag < 0)
	{
		perror("msg send fail\n");
		return -1;
	
	}
	
	return 0;
}

