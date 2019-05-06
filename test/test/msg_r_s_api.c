/**
msg queue API
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <syslog.h>
#include "configs.h"

//我也不清楚消息的结构体该怎么去写，先以例子为准

typedef struct data{
	long mtype;
	int status;
	char time[20];
	char mtext[1024];
}data_t;

/****************************************
1 需要创建一个文件当作 socket

*****************************************/
int get_msg(app_t app)
{
	
	int msgid = -1;
	int reclen=0;
	struct msqid_ds info;
	int mytype;
 	data_t buf;

 	int flag =-1;
	int sndlen;
	int key;  //

	key = ftok("msg.tmp", 0x01); //大于0的32位整数：视参数msgflg来确定操作。通常要求此值来源于ftok返回的IPC键值
	if(key < 0)
	{
		test_log("can not receice");
		return -1;
	}
	msgid = msgget(key,0);//0：取消息队列标识符，若不存在则函数会报错
	reclen = sizeof(data_t) - sizeof(long);
	mytype =(long)app;
	memset(&buf, 0, reclen);
	
	while(1)
	{
			flag = msgrcv(msgid, &buf, reclen, mytype, 0);
			test_log("type=%ld, time %s ,message %s\n", buf.mtype, buf.time, buf.mtext);
			if(flag < 0)
			{
				test_log("recv message fail\n");
				return -1;
			}
			test_log("key %lx \n msgid %ld \n",key, msgid);
			system("ipcs -q");
	}	
	return 0;
}
/********************************************
send
********************************************/
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

//context有长度限制
int send_msg(app_t app, const char* context)
{
	int msgid; //queue ID
	data_t buf;
	struct msqid_ds info; 
	data_t buf2;

	int flag =-1;
	int sndlen, reclen;
	int key;


	key = ftok("msg.tmp", 0x01);
	if(key < 0)
	{
		test_log("fotk fail \n");
		return -1;
	}
	/*IPC_CREAT：当msgflg&IPC_CREAT为真时，
	如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；
	如果存在这样的消息队列，返回此消息队列的标识符
	IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错*/
	msgid = msgget(key, 0600|IPC_CREAT); 
	if(msgid < 0)
	{
		test_log("create msg queue error\n");
		return -1;
	}
	buf.mtype =(long)app;
	buf.status = 9;
	strcpy(buf.time, get_local_time());
	strcpy(buf.mtext,context);
	sndlen = sizeof(data_t) - sizeof(long);
	flag = msgsnd(msgid, &buf, sndlen, 0); // 0 ?
	if (flag < 0)
	{
		test_log("msg send fail\n");
		return -1;
	}
	
	return 0;
}

