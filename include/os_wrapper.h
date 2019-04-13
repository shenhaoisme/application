/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     os_wrapper.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Os wrapper header file
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
  - 2009/10/15 Vivien ZHU
  smrc00030005 Debug out of range function.
  - 2011/03/08 Terry Zhao
    Wrk(crms00299420),Cr(crms00259958) VHE[BT-regression]:Sometime, BT process go to die
-------------------------------------------------------------------- */

/** @defgroup group3 OSWrapper
 *  This is the group of OS Wrapper Layer
 *  @{
 */

#ifndef _OS_WRAPPER_H_
#define _OS_WRAPPER_H_

/*------------------------------------------------------------------
 * Module Macro and Type definitions
 * Module Variables Definitions
 *------------------------------------------------------------------*/

/*!
 * \def DONT_WAIT
 *  Semaphore use it as parameter to trigger a sem_trywait .
 */
#define DONT_WAIT   0

/*!
 * \def SUSPEND
 *  Semaphore use it as parameter to trigger a sem_wait .
 */
#define SUSPEND     -1

/*-------------------------------------------------------------------
  Threads
  -------------------------------------------------------------------*/

/*!
 * \enum thread_id_t
 *      The Thread IDs
 */
typedef enum {
    THREAD_ID_shell         = 0,    //!< Shell Thread
    THREAD_ID_bluetooth     = 1,
    THREAD_ID_afh           = 2,
    THREAD_ID_MAX
} thread_id_t;

/*!
 * Creates a type name for thread entry point function type
 */
typedef void thread_entry_t(void);

/*------------------------------------------------------------------
  Queues
  ------------------------------------------------------------------*/

/*!
 * \enum msgQ_id_t
 * The User Message Queue IDs
 */
typedef enum {
    QUEUE_ID_none = 0,
    QUEUE_ID_shell = 1, /*!< User Message Queue for Shell */
    QUEUE_ID_bluetooth = 2,
    QUEUE_ID_MAX
} msgQ_id_t;

/*! Creates a type msg_t name for S_PRIMITIVE */
typedef S_PRIMITIVE msg_t;

/*------------------------------------------------------------------
  Semaphore
  ------------------------------------------------------------------*/

/*!
 * \enum sem_id_t
 * The User Semaphore IDs
 */
typedef enum {
    SEM_ID_fast_pairing  = 0,
    SEM_ID_btdevmgr_list  = 1,
    SEM_ID_MAX
} sem_id_t;

/*------------------------------------------------------------------
 * Module External functions Declaration
 *------------------------------------------------------------------*/

int     oswrapper_init  (void);
void    oswrapper_term  (void);

/*------------------------------------------------------------------
 * Thread
 *------------------------------------------------------------------*/

/*!
 * \def thread_create(id,entry)
 *  Create thread with \a id and function \a entry.
 */
#define thread_create(id,entry) _thread_create(__FILE__, __LINE__, id, entry)

/*!
 * \def thread_delete(id)
 *  Delete thread which has \a id.
 */
#define thread_delete(id)       _thread_delete(__FILE__, __LINE__, id)

extern int _thread_create(const char *filename, int linenum,
         thread_id_t id, thread_entry_t entry);

extern int _thread_delete(const char *filename, int linenum,
         thread_id_t id);

/*------------------------------------------------------------------
 * Message Queue
 *------------------------------------------------------------------*/

/*!
 * \def msgQ_send(id, msg)
 *  Send a message into a message queue.
 */
#define msgQ_send(id, msg)    _msgQ_send(__FILE__, __LINE__, id, msg)

/*!
 * \def msgQ_recv(id, msg)
 *  Receive a message from a message queue.
 */
#define msgQ_recv(id, msg)    _msgQ_recv(__FILE__, __LINE__, id, msg)

extern int _msgQ_send(const char *filename, int linenum,
   msgQ_id_t            id,
   msg_t                msg
);

extern int _msgQ_recv(const char *filename, int linenum,
   msgQ_id_t            id,
   msg_t &              msg
);

/*------------------------------------------------------------------
 * Semaphore
 *------------------------------------------------------------------*/

/*!
 * \def sem_create(id, ini_val)
 *  Create a semaphore.
 */
#define sem_create(id, ini_val) \
                          _sem_create(__FILE__, __LINE__, id, ini_val)

/*!
 * \def sem_delete(id)
 *  Delete a semaphore.
 */
#define sem_delete(id)    _sem_delete(__FILE__, __LINE__, id)

/*!
 * \def sem_give(id)
 *  giving a semaphore.
 */
#define sem_give(id)    _sem_give(__FILE__, __LINE__, id)

/*!
 * \def sem_get(id)
 *  waiting for a semaphore.
 */
#define sem_get(id,timeout) _sem_get (__FILE__, __LINE__, id, timeout)

/*!
 * \def sem_reset(id)
 *  Reset a semaphore.
 */
#define sem_reset(id)       _sem_reset(__FILE__, __LINE__, id)


extern int _sem_create(const char *filename, int linenum,
         sem_id_t id, uint32_t ini_value);

extern int _sem_delete(const char *filename, int linenum,
         sem_id_t id);

extern int _sem_give(const char *filename, int linenum,
         sem_id_t id);

extern int _sem_get (const char *filename, int linenum,
         sem_id_t id, int32_t timeoutms);

extern int _sem_reset(const char *filename, int linenum,
         sem_id_t id);

//crms00152015 Vivien ZHU+
typedef void (*bt_timer_handler)(int);
#if 0 /*by shiyan*/
void bt_timer_init(int tv_sec,int tv_usec,bt_timer_handler timer_handler);
void bt_timer_stop(void);
#else
int bt_init_timer(bt_timer_handler timer_handler,timer_t * tid);
int  bt_start_timer(timer_t timerid,int tv_sec,int tv_usec,int Repeat);
int  bt_stop_timer(timer_t timerid);
#endif

//crms00152015 Vivien ZHU-
#endif//_OS_WRAPPER_H_

/** @} */ // end of group OSWrapper

