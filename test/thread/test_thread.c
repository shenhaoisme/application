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

//几个盲点：
//线程创建会自动运行。有时候没有结果，是因为进程执行结束推出了
//线程创建以后，放在后端运行，print还是可以用的，应该是和进程使用同一个终端
static void * callback(void* arg)  //can input one arg
{
	struct member *temp;
	
	printf("thread start \n");
	
	sleep(1);
	temp = (struct member*) arg;
	printf("num is %d \n", temp->num);
	printf("name is %s\n", temp->name);
	
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
	//我发现当打印1s的时候，线程callback函数的print没有来得及执行结束
	//
	//sleep(2);
	//也可以直接调用等待函数
	if(pthread_join(tid_p, NULL)) //wait the thread exit 
	{
		printf("thread is not exit...  normally\n");
		return -2;
	}
	printf("get pid %ld",getpid());
	printf("gettid %ld",(long int)syscall(224));
	printf("gettid %ld", (long int)syscall(__NR_gettid));
	return 0;
}
/*--------------------   second example ---------------------------*/
//把filename 和 line 也封装进去
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
