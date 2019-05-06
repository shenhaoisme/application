#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>  //
#include <sys/syscall.h>//for gettid



#include "test_log.h"
//int pthread_create(pthread_t *restrict tidp,const pthread_attr_t *restrict_attr,void*（*start_rtn)(void*),void *restrict arg);
/**
　 第一个参数为指向线程标识符的指针。

　　第二个参数用来设置线程属性。

　　第三个参数是线程运行函数的地址。

　　最后一个参数是运行函数的参数。
*/

struct member
{
	int num;
	char *name;
};

// callback
static void * callback(void* arg)  //can input one arg
{
	struct member *temp;
	
	printf("thread start !!");
	
	sleep(1);
	temp= (struct member*) arg;
	printf("num is %d", temp->num);
	printf("name is %s", temp->name);
	
	return NULL;
}
/* attr is null*/
int test(void)
{
	pthread_t tid_p;
	struct member *m;
	m=(struct member*) malloc(sizeof(struct member)); //create a var
	
	m->num=25;
	m->name="shenhao";
	
	if(pthread_create(&tid_p, NULL, callback, (void*)m) == -1)
	{
		printf("creat fail\n");
		return -1;
	}
	sleep(1);
	test_log("id %d ", tid_p);
	if(pthread_join(tid_p, NULL)) //wait the thread exit 
	{
		printf("thread is not exit...\n");
		return -2;
	}
	test_log("get pid %ld",getpid());
	test_log("gettid %ld",(long int)syscall(224));
	test_log("gettid %ld", (long int)syscall(__NR_gettid));
	return 0;
}
/*--------------------   second example ---------------------------*/


#define thread_creat(tid, entry) _thread_create(__FILE__, __LINE__, tid, entry)
typedef void thread_entry_t(void);
#define THREAD_MAX 10
typedef struct
{
	pthread_t* tid;
	thread_entry_t *_entry;
}map_thread_t;
static map_thread_t thread_array[THREAD_MAX];
/*callback for test_thread*/
void test_entry(void)
{
	printf("shenhao!!\n");
}


/*re-wirte ale thread_create function
@note 1 : it is general function, so fikename and linenum are both meaningful
@note 2 : thread_entry_t : 
	typedef void thread_entry_t(void); <pointer of func>
@note 3 : 



*/
int _thread_create(const char * filename, int linenum, pthread_t* tid, thread_entry_t entry)
{
	pthread_attr_t attr;
	pthread_t m_tid;

	int r, rs =0;
	rs = pthread_attr_init( &attr );
	if (rs!=0) {
        printf( "pthread_attr_init failed, in %s at %d line. ",filename, linenum );
        return -1;
    }
	
	r = pthread_create(&m_tid, &attr,(void *(*)(void*)) entry, NULL);
	if (r!=0) {
        printf( "thread creation failed, in %s at %d line. ",filename, linenum );
        return -1;
    }
	else
		//thread_array[tid]._entry= entry;
	
	rs = pthread_attr_destroy(&attr);
	if(rs != 0)
		 printf( "pthread attribute destroy failed in %s at %d line. ",filename, linenum );
		
	return 0;
}

int main()
{
	test();
	//pthread_t* tid;
	//thread_creat((pthread_t*)tid, test_entry);
	
	return 0;
	
}
