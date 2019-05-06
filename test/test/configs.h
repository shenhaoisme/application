/*
把所有的声明都放在一起
*/

#include <syslog.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <syslog.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define bool _Bool


//线程callback声明
typedef void thread_entry_t(void);

//目前设计的 app
typedef struct
{
	pthread_t* tid;
	thread_entry_t *_entry;
}map_thread_t;
typedef enum
{
	APP1=1,
	APP2=2,
	THREAD_MAX
}app_t;

static map_thread_t thread_array[THREAD_MAX];


/*----syslog------*/

#define test_log(...) syslog(LOG_EMERG, __VA_ARGS__)

/*------thread API-------------*/
#define thread_creat(tid, entry) _thread_create(__FILE__, __LINE__, tid, entry)
int _thread_create(const char * filename, int linenum, app_t tid, thread_entry_t entry);

/*-------app api---------------*/
void run(app_t app, bool background);
pthread_t get_tid(app_t app);


/*---------msg receive or add api---------------*/
int send_msg(app_t app, const char* context);
int get_msg(app_t app);
