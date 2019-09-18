#ifndef _THREADAPI_H_
#define _THREADAPI_H_

#include <pthread.h>

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

//每个线程的callback都不一样
typedef void thread_entry_t(void); //只有有一个param


//封装 filename 和 linenum
//#define thread_create(id,entry) _thread_create(__FILE__, __LINE__, id, entry, NULL) //ale
#define thread_creat(tid, entry) _thread_create(__FILE__, __LINE__, tid, entry)
#define THREAD_MAX 10
typedef struct
{
	pthread_t* tid;
	thread_entry_t *_entry;
}map_thread_t;

static map_thread_t thread_array[THREAD_MAX];














#endif