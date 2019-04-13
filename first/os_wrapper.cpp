/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
 ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
 ------------------------------------------------------------------ \n
  \file     os_wrapper.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    OS Wrapper Source
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
  - 2009/10/15 Vivien ZHU
  smrc00030005 Debug out of range function.
  - 2009/12/14 David MA                                             \n
  crms00205297 Optimize log usage in btmgr.
  - 2011/03/08 Terry Zhao
    Wrk(crms00299420),Cr(crms00259958) VHE[BT-regression]:Sometime, BT process go to die
  - 2011/10/08 David MA
    Wrk(crms00340903),Cr(crms00338643) [OXE][ICE][VHE]:Bluetooth bandset BTH no more working
 */

/*------------------------------------------------------------------
 * System includes
 *------------------------------------------------------------------*/

#   include <sys/types.h>
#   include <sys/ipc.h>
#   include <sys/msg.h>
#   include <sys/errno.h>
#   include <time.h>
#   include <stdlib.h>

#   include <unistd.h>
#   include <pthread.h>
#   include <semaphore.h>

#   include <stdio.h>
#   include <string.h>
//crms00152015 Vivien ZHU+
#   include <sys/time.h>
#   include <signal.h>
#   include <sys/timeb.h>
//crms00152015 Vivien ZHU-

/*------------------------------------------------------------------
 * Module includes
 *------------------------------------------------------------------*/

#include "stdinc.h"
#include "syslog.h"
#include "primitive.h"
#include "os_wrapper.h"

/** @defgroup group3 OSWrapper
 *  This is the group of OS Wrapper Layer
 *  @{
 */

/*------------------------------------------------------------------
 * Module Macro and Type definitions
 * Module Variables Definitions
 *------------------------------------------------------------------*/

/*!
 * \def UNDEF
 *    Define an unvalid value for thread and message queue.
 */
#define UNDEF        0

/*-------------------------------------------------------------------
 Threads
 -------------------------------------------------------------------*/

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
    const char *name; //!< thread name
    int priority; //!< thread priority : 99 <-> highest, 1 <-> lowest in Linux

    OSTYPE_THREAD id; //!< thread id
    thread_entry_t *entryPoint; //!< thread entry point function

} map_thread_t;

/*!
 * \brief A global variable to save the list of all threads name and priority
 */
static map_thread_t thread_array[THREAD_ID_MAX] =
{
{ "Shell", 0, UNDEF, NULL },
{ "bluetooth", 0, UNDEF, NULL } };

/*------------------------------------------------------------------
 Queues
 ------------------------------------------------------------------*/

/*!
 * \def OSTYPE_MSGQ
 *  Define int as OSTYPE_MSGQ
 */
#define OSTYPE_MSGQ  int

/*!
 *  \brief This is a queue structure.
 */
typedef struct
{
    const char *name; //!< Name of Queue
    OSTYPE_MSGQ id; //!< Queue id
} map_queue_t;

/*!
 * \brief A global value to save system message Queue ID
 */
OSTYPE_MSGQ msgQ_id = UNDEF;

/*!
 * \brief A global variable to save the list of message Queue name and ID
 */
static map_queue_t msgQ_array[QUEUE_ID_MAX] =
{
{ "none", QUEUE_ID_none },
{ "shell", QUEUE_ID_shell },
{ "bluetooth", QUEUE_ID_bluetooth } };

/*------------------------------------------------------------------
 Semaphores
 ------------------------------------------------------------------*/

/*!
 * \def OSTYPE_SEM
 *  Define sem_t pointer as OSTYPE_SEM
 */
#define OSTYPE_SEM  sem_t *

/*!
 *  \brief This is a semaphore structure.
 */
typedef struct
{
    const char *name; //!< Name of Semaphore
    OSTYPE_SEM id; //!< Semaphore id
} map_sem_t;

/*!
 * \brief A global variable to save the list of semaphore name and ID
 */
static sem_t semaphore[SEM_ID_MAX];

/*!
 * \brief A global variable to save the list of semaphore name and ID
 */
static map_sem_t sem_array[SEM_ID_MAX] =
{
{ "pairing", UNDEF },
{ "btlist", UNDEF },
};

/*------------------------------------------------------------------
 * Module Internal functions Definitions
 *------------------------------------------------------------------*/

/*!
 * \brief Set Thread Priority
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param pattr     : thread attribute
 * \param priority  : thread priority : 99 <-> highest, 1 <-> lowest in Linux
 *
 * \return int
 *          - positive  : successful
 *          - others    : failure
 */
static int set_thread_priority( const char *filename, int linenum,
    pthread_attr_t *pattr,
    int priority
)
{
    struct sched_param sched;
    int rs;
    int newpriority = 0;
    //int oldpriority;

    rs = pthread_attr_getschedparam( pattr, &sched );
    if (rs!=0) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "pthread_attr_getschedparam failed" );
        return -1;
    }

    //oldpriority = sched.__sched_priority;
    sched.__sched_priority = priority;

    rs = pthread_attr_setschedparam( pattr, &sched );
    if (rs!=0) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "pthread_attr_setschedparam failedv" );
        return -2;
    }

    rs = pthread_attr_getschedparam( pattr, &sched );
    if (rs!=0) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "pthread_attr_getschedparam failed" );
        return -3;
    }
    newpriority = sched.__sched_priority;

    return newpriority;
}


/*------------------------------------------------------------------
 * Module External functions Definitions
 *------------------------------------------------------------------*/

/*!
 * \brief OS Wrapper Layer Initialzation
 * Create one general system message queue and enable thread cancelable
 *
 * \return int
 *          - 0     : successful
 *          - others: failure
 */
int oswrapper_init(void)
{
    /* message queue creation */

    int msgQid;

    msgQid = msgget(IPC_PRIVATE, (IPC_CREAT|IPC_EXCL|0666));
    if (msgQid < 0) {
           syslog( __FILE__, __LINE__,
            FLUX_BT, LOG_FATAL, "Message Queue creation failed" );
           return -1;
    }

    /* Save it into global variable */
    msgQ_id = msgQid;

    /* thread attribute */

    int state, oldstate;

    state = PTHREAD_CANCEL_ENABLE;
    if ( 0 != pthread_setcancelstate(state, &oldstate) )
    {
        syslog( __FILE__, __LINE__,
                FLUX_BT, LOG_ANOMALY, "thread setcancelstate failed" );
    }

    return 0;
}

/*!
 * \brief OS Wrapper Layer Termination
 * The general system message queue will be deleted.
 */
void oswrapper_term(void)
{
    /* message queue deletion */
    if (UNDEF != msgQ_id)
    {
        if ( 0 != msgctl(msgQ_id, IPC_RMID, NULL) )
        {
            syslog( __FILE__, __LINE__,
                    FLUX_BT, LOG_ANOMALY, "message queue delete failed" );
        }
        msgQ_id = UNDEF;
    }

    return;
}

/*!
 * \brief initialize and activate a thread
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Thread ID
 * \param entry     : Thread Entry Point Function
 *
 * \return int
 *          - 0     : successful
 *          - others: failure
 */
int _thread_create(const char *filename, int linenum,
         thread_id_t id, thread_entry_t entry)
{
    int r;
    pthread_attr_t attr;
    int rs;

    rs = pthread_attr_init( &attr );
    if (rs!=0) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "pthread_attr_init failed" );
        return -1;
    }

    if ( thread_array[id].priority > 0 ){
        set_thread_priority( filename, linenum, &attr, thread_array[id].priority );
    }

    r = pthread_create((pthread_t *)&thread_array[id].id,
               &attr,
               (void *(*)(void *))entry,
               NULL);
    if (r != 0)
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "thread creation failed" );
    }
    else{
        thread_array[id].entryPoint = entry;
    }

    rs = pthread_attr_destroy( &attr );
    if (rs!=0) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "pthread attribute destroy failed" );
    }

    return 0;
}

/*!
 * \brief delete a previously created thread
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Thread ID
 *
 * \return int
 *          - 0 : successful
 *          - others : failure
 */
int _thread_delete(const char *filename, int linenum, thread_id_t id)
{
    int ret = 0;
    pthread_t tid;

    if (id < THREAD_ID_MAX)
    {
        tid = thread_array[id].id;
        if (tid==UNDEF) {
            ret = -1;
        }
        else
        {
            if (0 != pthread_cancel(tid))
            {
                syslog( filename, linenum,
                        FLUX_BT, LOG_ANOMALY, "thread terminate failed" );
                ret = -2;
            }
            thread_array[id].id = UNDEF;
        }
    }

    return ret;
}


/*!
 * \brief send message to message queue
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : User Message Queue ID
 * \param msg       : A primitive message
 *
 * \return int
 *          - 0       : Success
 *          - others  : Failure
 */
int _msgQ_send(const char *filename, int linenum,
   msgQ_id_t            id,
   msg_t                msg
)
{
    struct {
        long  mtype;    /* message type */
        msg_t mtext;    /* message data */
    } themsg;

    long msqid;

    if ((id < 0) || (id >= QUEUE_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Queue ID out of range" );
        return -1;
    }
    msqid = msgQ_array[id].id;

    themsg.mtype = msqid;
    themsg.mtext = msg;

    if (0 != msgsnd(msgQ_id, (struct msgbuf *)&themsg, sizeof(msg_t), IPC_NOWAIT))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Message send failure" );
        return -2;
    }
//crms00338643 David MA+
#if 0
    syslog( filename, linenum,
            FLUX_BT, LOG_DEBUG, "msgQ_send: message send, queue = %s",
            msgQ_array[id].name );//crms00152015 David MA
#endif
//crms00338643 David MA-
    return 0;
}

/*!
 * \brief receive message from message queue
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : User Message Queue ID
 * \param msg       : A primitive message
 *
 * \return int
 *          - 0       : Success
 *          - others  : Failure
 */
int _msgQ_recv(const char *filename, int linenum,
   msgQ_id_t            id,
   msg_t &              msg
)
{
    int msqid;
    struct {
        long mtype;     /* message type */
        msg_t mtext;    /* message data */
    } themsg;

    if ((id < 0) || (id >= QUEUE_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Queue ID out of range" );
        return -1;
    }

    msqid = msgQ_array[id].id;
    if (-1 == msgrcv(msgQ_id, (struct msgbuf *)&themsg, sizeof(msg_t), msqid, 0))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Message receive failure" );
        return -2;
    }

#if 0
    syslog( filename, linenum,
            FLUX_BT, LOG_DEBUG, "msgQ_recv: message receive, queue = %s id =%d",
            msgQ_array[id].name, msgQ_array[id].id );//crms00152015 David MA
#endif

    msg = themsg.mtext;

    return 0;
}

/*!
 * \brief initialize a semaphore
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Semaphore ID
 * \param ini_value : Initial value of this semaphore
 *
 * \return int
 *          - 0     : success
 *          - others: failure
 */
int _sem_create(const char *filename, int linenum,
         sem_id_t id, uint32_t ini_value)
{
    OSTYPE_SEM   sem_id;

    if ((id < 0) || (id >= SEM_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Semaphore ID out of range" );
        return -1;
    }

    sem_id = sem_array[id].id;
    if ( sem_id != UNDEF ) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Semaphore already created, can't repeat creating" );
        return -2;
    }

    sem_id = &semaphore[id];
    if ( 0 != sem_init( sem_id, 0, ini_value ) ){
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "semaphore creation failed" );
        return -3;
    }

    sem_array[id].id = sem_id;

    return 0;
}

/*!
 * \brief delete a semaphore
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Semaphore ID
 *
 * \return int
 *          - 0     : success
 *          - others: failure
 */
int _sem_delete(const char *filename, int linenum, sem_id_t id)
{
    OSTYPE_SEM   sem_id;

    if ((id < 0) || (id >= SEM_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Semaphore ID out of range" );
        return -1;
    }

    sem_id = sem_array[id].id;
    if ( sem_id == UNDEF ) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Semaphore no creation, can't delete" );
        return -2;
    }

    if ( 0 != sem_destroy( sem_id ) ){
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "semaphore deletion failed" );
        sem_array[id].id = UNDEF;
        return -3;
    }

    sem_array[id].id = UNDEF;

    return 0;
}

/*!
 * \brief giving a semaphore
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Semaphore ID
 *
 * \return int
 *          - 0     : success
 *          - others: failure
 */
int _sem_give(const char *filename, int linenum,
         sem_id_t id)
{
    OSTYPE_SEM   sem_id;

    if ((id < 0) || (id >= SEM_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't exist" );
        return -1;
    }

    sem_id = sem_array[id].id;
    if ( sem_id == UNDEF ) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't initialize" );
        return -2;
    }

    if ( 0 != sem_post( sem_id ) ){
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "semaphore giving failed" );
        return -3;
    }

    return 0;
}

/*!
 * \brief waiting for a semaphore
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Semaphore ID
 * \param timeoutms : wait timeout (ms)
 *                      -  0 : sem_trywait  , return immediately
 *                      - <0 : sem_wait     , suspend if no semaphore
 *                      - >0 : sem_timedwait
 *
 * \return int
 *          - 0     : success to get a semaphore
 *          - 1     : timeout
 *          - <0    : failure
 */
int _sem_get(const char *filename, int linenum,
         sem_id_t id, int32_t timeoutms)
{
    OSTYPE_SEM      sem_id;
    int             retVal;
    struct timespec *abstime=NULL;

    if ((id < 0) || (id >= SEM_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't exist" );
        return -1;
    }

    sem_id = sem_array[id].id;
    if ( sem_id == UNDEF ) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't initialize" );
        return -2;
    }

    if ( timeoutms == 0 ) {
        if ( 0 == sem_trywait( sem_id ) ){
            return 0;
        }
        else {
            return -3;
        }
    }
    else if ( timeoutms < 0 ) {
        if ( 0 != sem_wait( sem_id ) ){
            syslog( filename, linenum,
                    FLUX_BT, LOG_ANOMALY, "sem_wait: semaphore getting failed" );
            return -4;
        }
    }
    else if ( timeoutms > 0 ) {
        struct timespec thetime;
        abstime = &thetime;
        clock_gettime(CLOCK_REALTIME, abstime);
        abstime->tv_sec  += timeoutms / 1000;
        abstime->tv_nsec += 1000000*(timeoutms - (timeoutms / 1000 * 1000));
        if ( abstime->tv_nsec >= 1000000000 ) {
             abstime->tv_sec  += 1;
             abstime->tv_nsec -= 1000000000 ;
        }
        /*
        syslog( filename, linenum,
                FLUX_BT, LOG_DEBUG,
                "sem_timedwait: tv_sec=%d, tv_nsec=%d",
                 abstime->tv_sec, abstime->tv_nsec );
                 */

        retVal = sem_timedwait( sem_id, abstime );
        if ((errno == ETIMEDOUT) || (retVal == 0))
        {
            // indicate it is a timeout
            if (retVal==0)  return 0;
            else            return 1;
        }
        else {
            syslog( filename, linenum,
                    FLUX_BT, LOG_ANOMALY, "sem_timedwait: semaphore getting failed" );
            return -5;
        }
    }

    return 0;
}

/*!
 * \brief Reset a semaphore
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : Semaphore ID
 *
 * \return int
 *          - 0     : success
 *          - others: failure
 */
int _sem_reset(const char *filename, int linenum,
         sem_id_t id)
{
    OSTYPE_SEM   sem_id;
    int          sval;
    int          i;

    if ((id < 0) || (id >= SEM_ID_MAX))
    {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't exist" );
        return -1;
    }

    sem_id = sem_array[id].id;
    if ( sem_id == UNDEF ) {
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "Target semaphore doesn't initialize" );
        return -2;
    }

    if ( 0 != sem_getvalue( sem_id, &sval ) ){
        syslog( filename, linenum,
                FLUX_BT, LOG_ANOMALY, "semaphore getvalue failed" );
        return -3;
    }

    for ( i = 0; i < sval; i++ ) {
        sem_trywait( sem_id );
    }

    return 0;
}
#if 0  /*crqms00159471 by shiyan*/
//crms00152015 Vivien ZHU+
void bt_timer_init(int tv_sec,int tv_usec,bt_timer_handler timer_handler)
{
    struct itimerval value;
    signal(SIGALRM, (*timer_handler));

    value.it_value.tv_sec = tv_sec;
    value.it_value.tv_usec = tv_usec;
    value.it_interval.tv_sec = tv_sec;
    value.it_interval.tv_usec = tv_usec;

    setitimer(ITIMER_REAL, &value, NULL);
}

void bt_timer_stop(void)
{
    struct itimerval value;

    value.it_value.tv_sec = 0;
    value.it_value.tv_usec = 0;
    value.it_interval.tv_sec = 0;
    value.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &value, NULL);
}
//crms00152015 Vivien ZHU-
#else
int bt_init_timer(bt_timer_handler timer_handler,timer_t * tid )
{
	struct sigaction act;      
	memset(&act, 0, sizeof(act));   

	act.sa_handler = timer_handler;      
  act.sa_flags = 0;          
	sigemptyset(&act.sa_mask);        
	if (sigaction(SIGUSR1, &act, NULL) == -1)   
	{
		syslog(__FILE__, __LINE__, FLUX_BT, LOG_WARNING,"sigaction failed ......");
		return -1;     
	}     

  timer_t timerid;    
  struct sigevent evp; 	
	memset(&evp, 0, sizeof(struct sigevent));     
	evp.sigev_value.sival_ptr = &timerid; 
	evp.sigev_signo = SIGUSR1;      
	evp.sigev_notify = SIGEV_SIGNAL;     
	if (timer_create(CLOCK_REALTIME, &evp, &timerid) == -1)
	{     
	      syslog(__FILE__, __LINE__, FLUX_BT, LOG_WARNING,"timer_create failed ......");
	      return -1;   
	}    

	* tid = timerid;
	return 0;
}

int  bt_start_timer(timer_t timerid, int tv_sec,int tv_usec,int Repeat)
{
	struct itimerspec it;   
	if (Repeat){
		it.it_interval.tv_sec = tv_sec;    
		it.it_interval.tv_nsec =tv_usec;     
	}
	it.it_value.tv_sec = 2;    
	it.it_value.tv_nsec = 0;     
	if (timer_settime((timer_t)timerid, 0, &it, 0) == -1)    
	{         
	      syslog(__FILE__, __LINE__, FLUX_BT, LOG_WARNING,"timer_settime failed......");	       
		return -1;     
	}   

	return 0;
}
int  bt_stop_timer(timer_t timerid)
{
    if (timerid < 0)
	 	return -1;

      if(timer_delete ( (timer_t)timerid) == -1)
      	{
	      syslog(__FILE__, __LINE__, FLUX_BT, LOG_WARNING,"timer_settime failed......");	       
		    return -1;
      	}
	return 0;
}
#endif
/** @} */// end of group OSWrapper

