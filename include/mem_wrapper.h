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

#ifndef __MEM_WRAPPER_H
#define __MEM_WRAPPER_H

/**
 * Macro Definitions
 */
#define pw_malloc(size) pw_malloc_exec(size, __FILE__, __LINE__)
#define pw_free(ptr) pw_free_exec(ptr, __FILE__, __LINE__)
#define pw_memcpy(dst, ori, size) pw_memcpy_exec(dst, ori, size, __FILE__, __LINE__)
#define pw_memset(dst, c, size) pw_memset_exec(dst, c, size, __FILE__, __LINE__)

/**
 * Global Functions Declaration
 */
void* pw_malloc_exec(unsigned int size,  const char *file, const int line);
void pw_free_exec(void *ptr, const char *file, const int line);
void pw_memcpy_exec(void *dst, void *ori, unsigned int size, const char *func, const char *file, const int line);
void pw_memset_exec(void *dst, int c, unsigned int size, const char *func, const char *file, const int line);


#ifdef MEMORY_CHECK
void pw_mem_check_start(void);
void pw_mem_check_stop(void);
#endif

#endif
