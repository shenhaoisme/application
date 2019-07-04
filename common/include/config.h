#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>
#include <syslog.h>


#   include <pthread.h>
#   include <semaphore.h>
#	include <sys/syscall.h>
#   include <sys/errno.h>

#define IPC_QUEUE_APP1 0x11111111
#define IPC_QUEUE_APP2 0x22222222

#define OSTYPE_MSGQ  int
#define bool int
#define TRUE 1
#define FALSE 0
#define test_log(...) syslog(LOG_EMERG, __VA_ARGS__)


typedef enum
{
	APP1=1,
	APP2=2,
	THREAD_MAX
}app_t;
/*!
 *  \brief This is a queue structure.
 */
typedef struct
{
    const char   *name  ;   //!< Name of Queue
    OSTYPE_MSGQ  id     ;   //!< Queue id
} map_queue_t;

static map_queue_t msgQ_array[THREAD_MAX]={
	{"app1",1},
	{"app2",2}
};

typedef unsigned char uint8_t;
typedef struct{
	char text[100];
}msg_t;

/*线程中没有定义给kernel识别的ID
pid_t	thread_tid		;	//!< thread unique TID, refer to 'man gettid'
*/
typedef void thread_entry_t(void);

typedef struct
{
	pthread_t tid;  //是去给 pthread_create的TID参数
	thread_entry_t *_entry;
}map_thread_t;
static map_thread_t thread_array[THREAD_MAX];

//这个全局变量是 msgsnd msgrcv的识别ID 
static volatile OSTYPE_MSGQ msgQ_id = -1; 

#define msgQ_send(id, msg)    _msgQ_send(__FILE__, __LINE__, id, msg)
#define msgQ_recv(id, msg) _msgQ_recv(__FILE__, __LINE__, id, &msg, FALSE)
#define msgQ_recv_nowait(id, msg) _msgQ_recv(__FILE__, __LINE__, id, &msg, TRUE)

extern int _msgQ_send(const char *filename, int linenum, app_t id,
                      msg_t msg);

extern int _msgQ_recv(const char *filename, int linenum, app_t id,
                      msg_t *ptr_msg, bool nowait);
					  
#define thread_set_tid(id) _thread_set_tid(__FILE__, __LINE__, id)
extern void _thread_set_tid(const char *filename, int linenum,
		app_t id);					  
#define thread_creat(tid, entry) _thread_create(__FILE__, __LINE__, tid, entry)
extern int _thread_create(const char * filename, int linenum, app_t tid, thread_entry_t entry);					  
					  
/*------------------------------------------------------------------
 * Module External functions Declaration
 *------------------------------------------------------------------*/

int msg_init(void);
void oswrapper_term(void);

void run(app_t app, bool background);
pthread_t get_tid(app_t app);







