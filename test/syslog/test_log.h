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