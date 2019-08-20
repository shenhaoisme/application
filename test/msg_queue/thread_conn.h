#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
/*
现在几乎lib 和 ALE 的一模一样了
*/


#define UNDEF 0  //pthread_t 没有被分配, 或者queue ID没有被分配

//callback 函数类型
typedef void thread_entry_t(void);


//理论上，把callback定义好直接创建就好了，不知道创建这样一个结构体
//把信息都保存下来，有什么用。
//枚举是为了区别不同的线程
typedef enum{
	THREEAD_ID_TEST1 = 0,
	THREEAD_ID_TEST2 = 1,
	THREEAD_ID_MAX
}thread_id_t;

//线程结构体
typedef struct  
{
	const char * name;
	int priority; // 99: highest 1 lowest in linux
	pthread_t id;
	thread_entry_t * entry; // why is point
}thread_t;

//创建两个实例
static thread_t thread_array[] = {
	{"test1", 0, UNDEF, NULL},
	{"test2", 0, UNDEF, NULL}
};

//
int thread_creat(thread_id_t id, thread_entry_t entry)
{
	int r;
	pthread_attr_t attr;
	int rs = pthread_attr_init( &attr );
	if (rs!=0) {
        printf( "pthread_attr_init failed " );
        return -1;
    }
	//如果优先级被设定。 暂略
	if(thread_array[id].priority > 0){
		//set_thread_priority()
	}
	
	//创建线程
	r = pthread_create(&thread_array[id].id, &attr,(void *(*)(void*)) entry, NULL);
	if (r != 0)
	{
		printf("pthread_create fail\n\n");
	}
	else
		thread_array[id].entry;
	//把 attr 删掉
	//r = pthread_attr_destroy(&attr);
	//if(r != 0)
	//	 printf( "pthread attribute destroy failed");
	return 0;
}

/*------------------------------------------------------------------
 Queues
 添加枚举后，Long type就没什么用了。但也不能删
 ------------------------------------------------------------------*/ 
typedef enum{
	QUEUE_ID_none  = 0,
	QUEUE_ID_test1 = 1,
	QUEUE_ID_test2 = 2,
	QUEUE_ID_MAX
}msgQ_id_t;
/*!
 *  \brief This is a queue structure.
 */
typedef struct
{
    const char *name; //!< Name of Queue
    msgQ_id_t id; //!< Queue id
} map_queue_t;

//队列id只有一个，不同 message区分于 struct.type
int msgQ_id = UNDEF;

static map_queue_t msgQ_array[QUEUE_ID_MAX] =
{{"none", QUEUE_ID_none},
{"test1", QUEUE_ID_test1},
{"test2", QUEUE_ID_test2}};


typedef struct
{
	char mtext[256];
}msg_t;

int msgQ_recv(msgQ_id_t id, msg_t& msg)
{
	struct {
		long type;
		msg_t mtext;
	}my_text;
	//msg_t msg;
	int msqid = msgQ_array[id].id;
	if (id < 0 || id >= QUEUE_ID_MAX)
	{
		printf("出大事了\n");
	}
	if(-1 == msgrcv(msgQ_id, (struct msgbuf*)&my_text, sizeof(msg_t), msqid, 0))
	{
		printf("msg receive fail \n\n");
		return -1;
	}
	msg = my_text.mtext;
	return 0;
}

int msgQ_send(msgQ_id_t id, msg_t msg)
{
	struct{
		long type;
		msg_t mtext;
	}themsg;
	
	long msqid;
	msqid = msgQ_array[id].id;
	
	themsg.type = msqid;
	themsg.mtext = msg;
	
	if(0 != msgsnd(msgQ_id, (struct msgbuf *)&themsg, sizeof(msg_t),IPC_NOWAIT))
	{
		printf("message send fail\n\n");
		return -2;
	}
	
	return 0;
}