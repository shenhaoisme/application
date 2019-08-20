#include "thread_conn.h"
#include <unistd.h>
#include <string.h>
#include <error.h>
#include <syslog.h>

/*
假设右两个线程，两个线程。
首先仿照 ALE 把线程的信息都封装到一个结构体中。并设置一个枚举值去标识每个线程
同样仿照 ALE 把队列的信息也封装为结构体，并设置枚举值去标识msg的type

创建两个线程，主进程分辨发送两个message，根据不同的type，发到两个线程。
两个线程都只接受一次message，大小小于 256 B。主进程用 Join 去等待两个进程接收完信号推迟

关于 join 会导致段错误的情况，一般都是 thread_ID 出错了。
我出错：是直接直接使用了枚举值，哪有 id==0 的线程？

*/

void test1_thread_entry(void);
void test2_thread_entry(void);

//模拟noemmi 下会创建很多线程，一个基本的框架，每个线程会写一个init函数
//其实质就是创建一个线程，线程创建完成会自动运行
void test1_init()
{
	if(0 != thread_creat(THREEAD_ID_TEST1, test1_thread_entry))
	{
		printf("thread_creat fail\n");
	}
	else
		printf("THREAD_ID_TEST1 start\n");
}
void test2_init()
{
	if(0 != thread_creat(THREEAD_ID_TEST2, test2_thread_entry))
	{
		printf("thread_creat fail\n");
	}
	else
		printf("THREAD_ID_TEST1 start\n");
}

int   main(int ac, char ** av)
{
	//获取线程退出状态
	void * threadRet = NULL;
	test1_init();
	test2_init();
	msgQ_id = msgget(0, IPC_CREAT|0777);
	//msg 是用在一个进程中不同线程间的沟通
	//现在线程已经 start, so I send one msg to this thread
	msg_t send_msg1 = {"hello world"};
	msgQ_send(QUEUE_ID_test1, send_msg1);
	msg_t send_msg2 = {"ni hao shuai "};
	msgQ_send(QUEUE_ID_test2, send_msg2);
	

	//wait thread exit
	int ret;
	for(int it = 0; it < (int)THREEAD_ID_MAX ; it++ )
	{
		ret = pthread_join(thread_array[THREEAD_ID_TEST1].id, &threadRet);
		if(ret == 0)
			printf("the thread return value is %d\n", (char*)threadRet);
		else
			printf("pthread_join is fail : return %d\n", ret);
	}
	//while(1);
	return 0;
}

void test1_thread_entry(void)
{
	//thread_set_tid()
	//while(1)
	{
		msg_t msg; 
		//msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0);
		msgQ_recv(QUEUE_ID_test1, msg);
		
		printf(" receive A : %s\n", msg.mtext);
	}	
}
void test2_thread_entry(void)
{
	//thread_set_tid()
	//while(1)
	{
		msg_t msg; 
		//msgrcv(msqid, &msg, sizeof(msg.mtext), 1, 0);
		msgQ_recv(QUEUE_ID_test2, msg);
		
		printf(" receive A : %s\n", msg.mtext);
	}	
}


