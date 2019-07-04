#include "common.c"
char *get_local_time()
{
        time_t tv;
        static char buf[20];
        struct tm *tmp;
        tv = time(0); //
        tmp = localtime(&tv);
        sprintf(buf, "%02d:%02d:%02d",tmp->tm_hour,tmp->tm_min,tmp->tm_sec);
        return buf;
}
