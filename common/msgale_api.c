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
#include "os_wrapper.h"

#define TEXT_SIZE 512

struct msgbuf
{
	long mtype;
	int status;
	char time[20];
	char mtext[TEXT_SIZE];
};

int msg_init(void)
{
	int msgQid;
	/*IPC_CREAT：当msgflg&IPC_CREAT为真时，
	如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；
	如果存在这样的消息队列，返回此消息队列的标识符
	IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错*/
	msgQid = msgget(IPC_QUEUE_APP1,0600|IPC_CREAT);
	 if (msgQid < 0) {
           //syslog(FLUX_OSWRAP, LOG_FATAL, "Message Queue creation failed" );
           return -1;
    }
	//msgQ_id全局变量，send 和 
	msgQ_id = msgQid;
	int state, oldstate;

    state = PTHREAD_CANCEL_ENABLE;
    if ( 0 != pthread_setcancelstate(state, &oldstate) )
    {
        //syslog(FLUX_OSWRAP, LOG_ANOMALY, "thread setcancelstate failed" );
    }

    return 0;
	
}
/*!
 * \brief OS Wrapper Layer Termination
 * The general system message queue will be deleted.
 */
void msg_term(void)
{
    /* message queue deletion */
    if (-1 != msgQ_id)
    {
        if ( 0 != msgctl(msgQ_id, IPC_RMID, NULL) )
        {
            //syslog(FLUX_OSWRAP, LOG_ANOMALY, "message queue delete failed" );
        }
        msgQ_id = -1;
    }

    return;
}

int _msgQ_send(const char *filename, int linenum, app_t id, msg_t msg)
{
    struct {
        long  mtype;    /* message type */
        msg_t mtext;    /* message data */
    } themsg;
    long msqid;

    if (id >= THREAD_MAX)
    {
       
        return -1;
    }
	//这id指发送哪个app，值在调用前设定ok
    msqid = msgQ_array[id].id; 

    themsg.mtype = msqid; // must be > 0 (= QUEUE_ID_dummy defined)
    themsg.mtext = msg;
	//多了一个 no wait
    if (0 != msgsnd(msgQ_id, (struct msgbuf *)&themsg, sizeof(msg_t), IPC_NOWAIT)) 
    {
       
        return -2;
    }
    return 0;
}


/*!
 * \brief receive message from message queue
 *
 * \param filename  : source file name in which this function is called
 * \param linenum   : source file line number in which this function is called
 * \param id        : User Message Queue ID
 * \param msg       : A primitive message
 * \param nowait    : true if don't want wait
 *
 * \return int
 *          - 0       : Success
 *          - others  : Failure
 */
int _msgQ_recv(const char *filename, int linenum, app_t id, msg_t* ptr_msg, bool nowait)
{
    int msqid;
    int flags;
    int ret;
    struct {
        long  mtype;    /* message type */
        msg_t mtext;    /* message data */
    } themsg;

    if (id >= THREAD_MAX)
    {
      
        return -1;
    }

    flags = 0;
    if (nowait)
        flags |= IPC_NOWAIT;

    msqid = msgQ_array[id].id;

    ret = msgrcv(msgQ_id, (struct msgbuf *)&themsg, sizeof(msg_t), msqid, flags);
    if ((-1 == ret) && (errno != ENOMSG))
    {
       
        return -2;
    }
	
    if (ret > 0)
        *ptr_msg = themsg.mtext;

    if (nowait)
    {
        if (ret > 0)
            return 0; // 0: success! got new message
        else
            return 1; // 1: no new message
    }
    else
    {
        return 0; // 0: success! got new message
    }
}



