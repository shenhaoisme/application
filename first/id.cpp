/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
 ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
 ------------------------------------------------------------------ \n
  \file     id.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    software identificaiton
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
 */

/*------------------------------------------------------------------
 * System includes
 *------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------
 * Module includes
 *------------------------------------------------------------------*/

#include "stdinc.h"
#include "id.h"

/*!
 * \brief	To judge if this version is released version or development version
 *
 * \return bool_t	: returns TRUE if application is a released version
 */
bool_t is_release_version(void)
{
    /// \todo: How to judge it is a release version ?
    return FALSE;   //return (released_version);
}
