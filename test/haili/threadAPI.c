
#   include <sys/types.h>
#   include <sys/ipc.h>
#   include <sys/msg.h>
#   include <sys/errno.h>
#   include <time.h>
#   include <stdlib.h>

#   include <unistd.h>
#   include <pthread.h>
#   include <semaphore.h>
#	include <sys/syscall.h>

#   include <stdio.h>
#   include <string.h>

#include "threadAPI.h"




/*!
 * \def OSTYPE_THREAD
 *    Define pthread_t as OSTYPE_THREAD.
 */
#define OSTYPE_THREAD  pthread_t

/*!
 *  \brief This is a thread structure.
 */
typedef struct
{
    const char    *name     ;   //!< thread name
    int           priority  ;   //!< thread priority : 99 <-> highest, 1 <-> lowest in Linux

    OSTYPE_THREAD id        ;   //!< thread id
    thread_entry_t *entryPoint; //!< thread entry point function
    bool_t 	is_running		;	//!< thread status
    pid_t	thread_tid		;	//!< thread unique TID, refer to 'man gettid'

} map_thread_t;


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