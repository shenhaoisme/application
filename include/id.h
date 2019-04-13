/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     id.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA,Viven ZHU
  \brief    software identification header file
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
-------------------------------------------------------------------- */

#ifndef _ID_H_
#define _ID_H_

//vivien+
#define VERSION_STR_LEN   8
//vivien-

/*!
 * \brief	To judge if this version is released version or development version
 *
 * \return bool_t	: returns TRUE if application is a released version
 */
extern bool_t is_release_version(void);



#endif /* _ID_H_ */

