#include "config.h"
//1 attr 我还不会用

/*!
 * \brief Inquiry the thread Unique TID. Must be called in thread internal context.
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Thread ID
 *
 * \return void
 */
/*void _thread_set_tid(const char *filename, int linenum,
		app_t id)
{
	if (id < THREAD_MAX){
		thread_array[id].thread_tid = syscall(SYS_gettid);	//gettid();
	}
	else{
	  
	}
	return;
}
*/
int _thread_create(const char * filename, int linenum, app_t tid, thread_entry_t entry)
{
	pthread_attr_t attr;
	pthread_t m_tid;

	int r, rs =0;
	rs = pthread_attr_init( &attr );
	if (rs!=0) {
        test_log( "pthread_attr_init failed, in %s at %d line. ",filename, linenum );
        return -1;
    }
	
	r = pthread_create(&m_tid, &attr,(void *(*)(void*)) entry, NULL);
	if (r!=0) {
        test_log( "thread creation failed, in %s at %d line. ",filename, linenum );
        return -1;
    }
	else
	{
		thread_array[(int)tid]._entry= entry;
		thread_array[(int)tid].tid= m_tid;
	}
		
	
	rs = pthread_attr_destroy(&attr);
	if(rs != 0)
		 test_log( "pthread attribute destroy failed in %s at %d line. ",filename, linenum );
		
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