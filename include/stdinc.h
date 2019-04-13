/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     stdinc.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Standard definition
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
-------------------------------------------------------------------- */

#ifndef _STDINC_H_
#define _STDINC_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*! Creates a type name for int8_t 	*/
typedef signed char   int8_t;

/*! Creates a type name for int16_t 	*/
typedef signed short  int16_t;

/*! Creates a type name for int32_t 	*/
typedef signed int    int32_t;

/* size_t type definition must be protected (arm lib)*/
#if !defined(__size_t) && ! defined(_SIZE_T)
#  define __size_t
#  define _SIZE_T  /* for sun */
typedef unsigned int        size_t;
#endif

/*! Creates a type name for uint8_t 	*/
typedef unsigned char   uint8_t;

/*! Creates a type name for uint16_t 	*/
typedef unsigned short  uint16_t;

/*! Creates a type name for uint32_t 	*/
typedef unsigned int    uint32_t;

/*! Creates a type name for bool_t 		*/
typedef uint8_t         bool_t;

#ifndef NULL
#  define NULL  0L
#endif

/*!
 * \def FALSE
 *      Define FALSE as 0
 */
#ifndef FALSE
#define FALSE   0
#endif

/*!
 * \def TRUE
 *      Define TRUE as 1
 */
#ifndef TRUE
#define TRUE    1
#endif

#endif /* _STDINC_H_ */
