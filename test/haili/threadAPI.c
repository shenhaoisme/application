#   include <sys/types.h>
#   include <sys/ipc.h>
#   include <sys/msg.h>
#   include <sys/errno.h>
#   include <time.h>
#   include <stdlib.h>

#   include <unistd.h>
#   include <pthread.h>
#   include <semaphore.h>
#	include <sys/syscall.h>

#   include <stdio.h>
#   include <string.h>

#include "threadAPI.h"


/*!
 * \def OSTYPE_THREAD
 *    Define pthread_t as OSTYPE_THREAD.
 */
#define OSTYPE_THREAD  pthread_t
#define THREAD_MAX 10

/*!
 *  \brief This is a thread structure.
 */
typedef struct
{
    int name     ;   //!< thread name 连接昵称
    //int           priority  ;  

    OSTYPE_THREAD id        ;   //!< thread id 标识不同的线程（连接）
    //每个连接调用的callback 都一样
    //thread_entry_t *entryPoint; //!< thread entry point function
    thread_status_t is_running	;	//!< thread status 是否在线
    pid_t	thread_tid		;	//!< thread unique TID, refer to 'man gettid' 类型应该是整型
} map_thread_t;


static map_thread_t thread_array[THREAD_MAX] = {};
/*-------------add client---------------------*/


//client做一个编号的动作，从0开始到10，总共会处理 11 个 client
static int number=0;
#define DECL_CLIENTNAME(number) CLIENT_##number
// int addClient(int id)
// {
	
// 	if(id == 0)
// 	{
// 		printf("using default nunber as ID\n");
// 	}
// 	else{
// 		printf("do nothing\n");
// 		return 0;
// 	}
	
// 	if(number < THREAD_MAX)｛
// 		thread_array[number] = {number, 0, FALSE, 0}; 
// 		number++;
// 	｝
// 	else
// 		return -1;
// 	return 0;
// }

thread_status_t _thread_set_status(const char *filename, int linenum,
		int id, thread_status_t status)
{
	if(id <= THREAD_MAX){  //10 is allowed
		thread_array[id].is_running = status;
	}
	else{
		printf("_thread_set_status invalid id=%d\n", id);
	}
	return thread_array[id].is_running;
}

thread_status_t _thread_get_status(const char *filename, int linenum,
		int id)
{
	if(id <= THREAD_MAX){  //10 is allowed
		return thread_array[id].is_running;
	}
	else{
		printf("_thread_set_status invalid id=%d\n", id);
	}
	
}

//
int get_name(int id)
{
	if(id <= THREAD_MAX){  //10 is allowed
		return thread_array[id].name;
	}
	else{
		printf("_thread_set_status invalid id=%d\n", id);
	}
}


/*re-wirte ale thread_create function
@note 1 : it is general function, so filename and linenum are both meaningful
@note 2 : thread_entry_t : 
	typedef void thread_entry_t(void); <pointer of func>
@note 3 : 
*/
int _thread_create(const char * filename, int linenum, int id, thread_entry_t entry)
{
	pthread_attr_t attr;
	//pthread_t m_tid;

	int r, rs =0;
	rs = pthread_attr_init( &attr );
	if (rs!=0) {
        printf( "pthread_attr_init failed, in %s at %d line. ",filename, linenum );
        return -1;
    }
	//因为创建的线程没有优先级可言，基于时间片轮转，给所有线程以公平的调度机会
	rs = pthread_attr_setschedpolicy(&attr, SCHED_RR);
	if(rs != 0)
	{
		printf("pthread_attr_setschedpolicy fails\n");
		rs = pthread_attr_destroy(&attr);
        if (rs != 0)
        {
            printf("pthread_attr_destroy fail\n");
        }
        return -1;
	}
	//thread_array[tid]._entry= entry;
	//把所有的线程都设置为  detached ，这样系统会自动回收线程的资源
	rs = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(rs != 0){
		printf("pthread_attr_setdetachstate fail\n");
		//释放资源	
	}


	//去创建线程
	r = pthread_create(&thread_array[id].id, &attr,(void *(*)(void*)) entry, NULL);
	if (r!=0) {
		thread_set_status(id, THREAD_IS_CLOSED);
        printf( "thread creation failed, in %s at %d line. ",filename, linenum );
    }
    else{
    	//创建成功就把status设置为true，为在线状态
    	thread_set_status(id, THREAD_IS_RUNNING); 
    	// if(addClient(0) == -1)
    	// {
    	// 	printf(" id %d is invalid\n", id);
    	// }
    	thread_array[number].id = number;
    	number++; 
    }
	
	rs = pthread_attr_destroy(&attr);
	if(rs != 0)
		 printf( "pthread attribute destroy failed in %s at %d line. ",filename, linenum );
		
	//给线程设置一个名字 昵称
	//pthread_setname_np(thread_array[id].id, thread_array[id].name);

	return 0;
}


