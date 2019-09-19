#ifndef _THREADAPI_H_
#define _THREADAPI_H_
#include <syslog.h>
#include <pthread.h>

//int pthread_create(pthread_t *restrict tidp,const pthread_attr_t *restrict_attr,void*（*start_rtn)(void*),void *restrict arg);
/**
　 第一个参数为指向线程标识符的指针。

　　第二个参数用来设置线程属性。

　　第三个参数是线程运行函数的地址。

　　最后一个参数是运行函数的参数。
*/


//每个线程的callback都不一样
typedef void thread_entry_t(void); //暂时不需要

/*!
 * \enum thread_status_t
 * The Thread Status IDs
 */
typedef enum {
    THREAD_IS_CLOSED    = 0, /*!< Closed */
    THREAD_IS_RUNNING	= 1, /*!< Running */
    THREAD_STATUS_MAX
} thread_status_t;



#define TRUE 1
#define FALSE 0
#define unsigned int bool_t



extern thread_status_t _thread_set_status(const char *filename, int linenum,
		int id, thread_status_t status);
extern thread_status_t _thread_get_status(const char *filename, int linenum,
		int id);

extern int get_name(int id);

//封装 filename 和 linenum
//#define thread_create(id,entry) _thread_create(__FILE__, __LINE__, id, entry, NULL) //ale
#define thread_creat(id, entry) _thread_create(__FILE__, __LINE__, id, entry)
#define thread_set_status(id,status) 	_thread_set_status(__FILE__, __LINE__, id, status)
#define thread_get_status(id) _thread_get_status(__FILE__, __LINE__, id)


#if 0
#define LOG_EMERG       0       /* system is unusable */
#define LOG_ALERT       1       /* action must be taken immediately */
#define LOG_CRIT        2       /* critical conditions */
#define LOG_ERR         3       /* error conditions */
#define LOG_WARNING     4       /* warning conditions */
#define LOG_NOTICE      5       /* normal but significant condition */
#define LOG_INFO        6       /* informational */
#define LOG_DEBUG       7       /* debug-level messages */

#endif


#include <syslog.h>
#define test_log(...) syslog(LOG_EMERG, __VA_ARGS__)
#define test_log_error(...) dtls_log(LOG_ALERT, __VA_ARGS__)
#define test_log_normal(...) dtls_log(LOG_CRIT, __VA_ARGS__)
#define test_log_debug(...) dtls_log(LOG_INFO, __VA_ARGS__)




#endif