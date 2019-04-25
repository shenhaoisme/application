#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

/*
只是简单发送message 发两次，一次type 为 1 ； 一次 type 为 3
*/
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
	key = ftok("msg.tmp", 0x01); //大于0的32位整数：视参数msgflg来确定操作。通常要求此值来源于ftok返回的IPC键值
	if(key < 0)
	{
		perror("can not receice");
		return -1;
	}
	
	msgid = msgget(key,0);//0：取消息队列标识符，若不存在则函数会报错
	reclen = sizeof(struct msgbuf) - sizeof(long);
	memset(&buf, 0, reclen);
	mytype=1;
	/*ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,

                      int msgflg);
					  
msgtyp

0：接收第一个消息

>0：接收类型等于msgtyp的第一个消息

<0：接收类型等于或者小于msgtyp绝对值的第一个消息
msgflg

0: 阻塞式接收消息，没有该类型的消息msgrcv函数一直阻塞等待

IPC_NOWAIT：如果没有返回条件的消息调用立即返回，此时错误码为ENOMSG

IPC_EXCEPT：与msgtype配合使用返回队列中第一个类型不为msgtype的消息

IPC_NOERROR：如果队列中满足条件的消息内容大于所请求的size字节，则把该消息截断，截断部分将被丢弃

*/
	while(1)
	{
		flag = msgrcv(msgid, &buf, reclen, mytype, 0);
	
		if(flag < 0)
		{
			perror("recv message fail\n");
			return -1;
		}
		
		printf("type=%ld, time %s ,message %s\n", buf.mtype, buf.time, buf.mtext);
		flag = msgrcv(msgid, &buf, reclen, 3, 0);
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
