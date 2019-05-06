#ifndef _OS_WRAPPER_H_
#define _OS_WRAPPER_H_
/*declare a array to save all thread's info; such as tid, name .....
id 和 tid 竟然不一样？


*/
typedef void thread_entry_t(void);
typedef struct
{
    const char *name;  //!< thread name
    int priority;      //!< thread priority : 99 <-> highest, 1 <-> lowest in Linux

    pthread_t id;            //!< thread id
    thread_entry_t *entryPoint;  //!< thread entry point function
    bool is_running;           //!< thread status
    pid_t thread_tid;            //!< thread unique TID, refer to 'man gettid'

} map_thread_t;
//这个用来区分线程
typedef enum{
	THREAD_ID_sun1 = 0,
	THREAD_ID_sun2 = 1, //怀疑多了一个逗号
	THREAD_ID_MAX
}thread_id_t;


extern int _thread_create(const char * filename, int linenum, thread_id_t tid, thread_entry_t entry);







#endif