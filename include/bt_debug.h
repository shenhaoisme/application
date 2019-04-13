/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     bt_debug.h
  \ingroup  ICTModule
  \date     09/01/2009
  \author   Viven ZHU
  \brief    Debug event
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 09/01/2009                                               \n
-------------------------------------------------------------------- */
#ifndef __BT_DEBUG_H
#define __BT_DEBUG_H

const char *ict_pBT_Status(I8 Status);
const char *ict_pME_Event(I8 event);
const char *ict_pHC_Status(U8 Status);
const char *ict_pHciEvent(U8 Event);
const char *ict_pHciCommand(U16 Cmd);

#endif
