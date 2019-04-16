/*
本质就是一个数组的初始化，只是把大括号换成了宏定义，而数组内容还是一个struct，而且每个结构体初始化的内容是重复的，
只有名字不一样，所以就又写了一个macro，只把名字给替换了而已。

这个用在
*/

#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include <bits/typesizes.h> //for pid_t
#define FALSE 0
#define UNDEF 0
typedef void thread_entry_t(void);
#define THREAD_ID_MAX 30
#define DECL_NORMAL(name)               \
    {                                   \
        #name, 0, UNDEF, NULL, FALSE, 0 \
    }
	
#define DECL_THREADS()                                                                 \
    DECL_NORMAL(main)                                                                  \
    ,                                       /*!< NOEMMI Main Thread(Just an ID here)*/ \
        DECL_NORMAL(nexgen),                /*!< Nexgen Thread(Just an ID here)     */ \
        DECL_NORMAL(shell),                 /*!< Shell Thread       */                 \
        DECL_NORMAL(timer),                 /*!< Timer Thread       */                 \
        DECL_NORMAL(display),               /*!< Display Thread     */                 \
        DECL_NORMAL(screenRefresh),         /*!< Screen Refresh Thread */              \
        DECL_NORMAL(dispevt),               /*!< Dispevt Thread     */                 \
        DECL_NORMAL(worker),                /*!< Worker Thread      */                 \
        DECL_NORMAL(keydrv),                /*!< Keydrv Thread      */                 \
        DECL_NORMAL(keyb),                  /*!< Keyb Thread        */                 \
        DECL_NORMAL(bridge),                /*!< Bridge Thread      */                 \
        DECL_NORMAL(command),               /*!< Command Thread     */                 \
        DECL_NORMAL(telnet),                /*!< Telnet Thread      */                 \
        DECL_NORMAL(curl_perform),          /*!< Curl Thread        */                 \
        DECL_NORMAL(sipapp_mgr),            /*!< Sip Application Manager Thread */     \
        DECL_NORMAL(sipapp_mgr_background), /*!< Sip Application Manager Thread */     \
        DECL_NORMAL(mouse_drive),           /*!< jianghoz add for mouse drive */       \
        DECL_NORMAL(jack_drive),            /*!< jianghoz add for jack drive */        \
        DECL_NORMAL(log_noemmi),            /*!< noemmi log Thread                  */ \
        DECL_NORMAL(minikbd),               /*!< Minikbd Thread (80x8ee)            */
		
		
typedef struct
{
    const char *name;  //!< thread name
    int priority;      //!< thread priority : 99 <-> highest, 1 <-> lowest in Linux

    pthread_t id;            //!< thread id
    thread_entry_t *entryPoint;  //!< thread entry point function
    bool is_running;           //!< thread status
    pid_t thread_tid;            //!< thread unique TID, refer to 'man gettid'

} map_thread_t;

static map_thread_t thread_array[THREAD_ID_MAX] = {DECL_THREADS()};



#define thread_create(id,entry) _thread_create(__FILE__, __LINE__, id, entry)

int _thread_create(const char *filename, int linenum,
         int id, thread_entry_t entry)
		 {
			 printf("%s\n",thread_array[id].name);
			 printf("%d\n",thread_array[id].priority);
			 printf("%d\n",thread_array[id].id);
		 }
void fun(void)
{
	printf("hello");
}
//#define locappl 
int main(void)
{
	thread_create(0,fun);
	return 0;
}




