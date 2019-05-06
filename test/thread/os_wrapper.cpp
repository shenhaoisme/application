#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "test_log.h"
#include "os_wrapper.h"
#define FALSE 0
#define UNDEF 0

/** 拼接成  一个 线程保存的数组 */
#define DECL_NORMAL(name)  {                                \
	#name, 0, UNDEF, NULL, FALSE, 0							\
}

#define DECL_THREADS()  \
	DECL_NORMAL(sun1), \
	DECL_NORMAL(sun2)
	
	
//真正用的 thread_creat
#define thread_creat(tid, entry) _thread_create(__FILE__, __LINE__, tid, entry)
// app 线城保存的数组
static map_thread_t thread_array[THREAD_ID_MAX] = {DECL_THREADS()};

int _thread_create(const char * filename, int linenum, thread_id_t appid, thread_entry_t entry)
{
	pthread_attr_t attr;

	int r, rs =0;
	rs = pthread_attr_init( &attr );
	if (rs!=0) {
        test_log( "pthread_attr_init failed, . ");
        return -1;
    }
	
	r = pthread_create((pthread_t *)&thread_array[appid].id, &attr,(void *(*)(void*)) entry, NULL);
	if (r!=0) {
        test_log( "thread creation failed,  ");
        return -1;
    }
	else
		thread_array[appid].entryPoint= entry;
	
	rs = pthread_attr_destroy(&attr);
	if(rs != 0)
		 test_log( "pthread attribute destroy failed ");
		
	return 0;
}


//test
void test(void)
{
	test_log("shenhao!!\n");
	return;
}
int main(int argc, char* argv[])
{
	thread_id_t appid = THREAD_ID_sun1;
	thread_creat(appid, test);
	thread_array[appid].entryPoint();
	return 0;
}



