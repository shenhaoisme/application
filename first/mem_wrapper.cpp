/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
  ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
  ------------------------------------------------------------------ \n
  \file     bt_debug.cpp
  \ingroup  ICTModule
  \date     05/27/2010
  \author   Terry Zhao
  \brief    memleak check
  \feature  (Cr)crms00233267, (Wrk)crms00233271
  \version  1.0

  History :                                                         \n
  create  : 05/27/2010                                              \n
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "mem_wrapper.h"
#include "syslog.h"


#ifdef MEMORY_CHECK

#define MAX_MEM_ALLOC_ARRAY_SIZE 300
#define MAX_FILE_NAME_LEN 100

typedef struct {
    void *addr;
    char filename[MAX_FILE_NAME_LEN+1];
    unsigned int line;
} MEM_ALLOC_SINGLE_T;

typedef struct {
    MEM_ALLOC_SINGLE_T array[MAX_MEM_ALLOC_ARRAY_SIZE];
    unsigned int count; //how many single alloc info
} MEM_ALLOC_T;

MEM_ALLOC_T mem_alloc_info;
pthread_mutex_t mem_mutex;
bool mem_check = false;
#endif


/**
 * GLOBAL FUNCTIONS DEFINITIONS
 */
/**
 * Allocate memory and Memset to 0
 */

void* pw_malloc_exec(unsigned int size, const char *file, const int line)
{
    if (size == 0)
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "Malloc size = 0!\n");

        return NULL;
    }
    else
    {
        void *ptr;

        ptr = malloc(size);

        if (ptr == NULL)
        {
            syslog(file, line, FLUX_BT, LOG_DEBUG, "Malloc error!\n");
        }
        else
        {
#ifdef MEMORY_CHECK
            if (mem_check)
            {
                pthread_mutex_lock(&mem_mutex);

                if (mem_alloc_info.count >= MAX_MEM_ALLOC_ARRAY_SIZE)
                {
                    syslog(file, line, FLUX_BT, LOG_DEBUG, "MAX_MEM_ALLOC_ARRAY_SIZE too small!!!\n");
                }
                else
                {
                    mem_alloc_info.array[mem_alloc_info.count].addr = ptr;
                    strncpy(mem_alloc_info.array[mem_alloc_info.count].filename, file, MAX_FILE_NAME_LEN);
                    mem_alloc_info.array[mem_alloc_info.count].line = line;

                    mem_alloc_info.count++;

                }

                pthread_mutex_unlock(&mem_mutex);

            }
#endif

            memset(ptr, 0, size);
        }

        return ptr;
    }
}


/**
 * Release memory
 */
void pw_free_exec(void *ptr, const char *file, const int line)
{
    if (ptr == NULL)
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "Free NULL pointer!\n");
    }
    else
    {
#ifdef MEMORY_CHECK
        if (mem_check)
        {
            unsigned int i;

            pthread_mutex_lock(&mem_mutex);

            for (i=0; i<mem_alloc_info.count; i++)
            {
                if (mem_alloc_info.array[i].addr == ptr)
                {
                    break;
                }
            }

            if (mem_alloc_info.count == i)
            {
                syslog(file, line, FLUX_BT, LOG_DEBUG, "%p NOT FOUND!!!\n", ptr);
            }
            else
            {
                if (i != (mem_alloc_info.count - 1))
                {
                    memcpy(&mem_alloc_info.array[i], &mem_alloc_info.array[mem_alloc_info.count-1], sizeof(MEM_ALLOC_SINGLE_T));
                }

                mem_alloc_info.count--;
            }

            pthread_mutex_unlock(&mem_mutex);
        }
#endif
        free(ptr);
    }
}


/**
 * Copy memory
 */
void pw_memcpy_exec(void *dst, void *ori, unsigned int size, const char *file, const int line)
{
    if (dst == NULL)
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "DST NULL\n");
    }
    else if (ori == NULL)
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "ORI NULL\n");
    }
    else
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "memcpy!\n");
        memcpy(dst, ori, size);
    }
}


/**
 * Set memory
 */
void pw_memset_exec(void *dst, int c, unsigned int size, const char *file, const int line)
{
    if (dst == NULL)
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "DST NULL\n");
    }
    else
    {
        syslog(file, line, FLUX_BT, LOG_DEBUG, "memset!\n");
        memset(dst, c, size);
    }
}


#ifdef MEMORY_CHECK
void pw_mem_check_start(void)
{
    pthread_mutex_init(&mem_mutex, NULL);
    mem_check = true;
    memset(&mem_alloc_info, 0, sizeof(mem_alloc_info));
}

void pw_mem_check_stop(void)
{
    unsigned int i;

    syslog(__FILE__, __LINE__, FLUX_BT, LOG_DEBUG, "MEME LEAK check\n");

    mem_check = false;
    pthread_mutex_destroy(&mem_mutex);

    syslog(__FILE__, __LINE__, FLUX_BT, LOG_DEBUG, "MEME LEAK:count:%d\n", mem_alloc_info.count);

    for (i=0; i<mem_alloc_info.count; i++)
    {
        syslog(__FILE__, __LINE__, FLUX_BT, LOG_DEBUG, "MEME LEAK::%p %s %d\n", mem_alloc_info.array[i].addr, mem_alloc_info.array[i].filename, mem_alloc_info.array[i].line);
    }
}
#endif

