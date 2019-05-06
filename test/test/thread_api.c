/*

*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include "configs.h"




//1 attr 我还不会用

int _thread_create(const char * filename, int linenum, app_t tid, thread_entry_t entry)
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
	{
		thread_array[(int)tid]._entry= entry;
		thread_array[(int)tid].tid= m_tid;
	}
		
	
	rs = pthread_attr_destroy(&attr);
	if(rs != 0)
		 printf( "pthread attribute destroy failed in %s at %d line. ",filename, linenum );
		
	return 0;
}

/*******************************
APP API
所有app都会去调用的api
********************************/
void run(app_t app, bool background)
{
	if(background)
		daemon(0,0);
	thread_array[(int)app]._entry();
}
pthread_t get_tid(app_t app)
{
	return thread_array[(int)app].tid;
}

/*
int create(void)
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
	
	return 0;
}
*/