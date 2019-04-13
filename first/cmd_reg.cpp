/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
 ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
 ------------------------------------------------------------------ \n
  \file     cmd_reg.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    command register file
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
  - 2009/12/01 Vivien ZHU                                           \n
    crms00201001 Add the BCCMD function.
    crms00203882 Change the bthid to btidcommand.
  - 2010/1/12 David MA                                              \n
    crms00208901 Update embedded commands in bthelp.
    crms00208911 Add a new embedded command to unpair a device.
  - 2010/3/08 David MA                                              \n
    Wrk(crms00218126) Cr(crms00213064) Recover BT Handset from      \n
                                       unexpected ATMEL upgrade     \n
                                       failure                      \n
  - 2010/5/21 David MA                                              \n
    Wrk(crms00232881),Cr(crms00232879) BT codec switch between CVSD \n
                                       and AURI                     \n
  - 2010/08/18 David MA
  Wrk(crms00253524),Cr(crms00246578) VHE[DFU]:During BT handset DFU, \n
  hook off BT handset,  BT handset can't be used unless unplug then  \n
  plug BT battery                                                    \n
 - 2011/03/08 Terry Zhao
    Wrk(crms00299420),Cr(crms00259958) VHE[BT-regression]:Sometime, BT process go to die
 - 2011/04/16 wenfangw
    PR(#261837):DFU function
 */

/*------------------------------------------------------------------
 * System includes
 *------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------
 * Module includes
 *------------------------------------------------------------------*/

#include "stdinc.h"
#include "syslog.h"
#include "shell.h"
#include "shell_exec.h"

/** @defgroup group1 The Embedded Commands
 *  This is the group of Bluetooth embedded commands
 *  @{
 */


/*
 * Define extern prototypes for all commands
 */

extern size_t CMD_help          (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_bth           (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btmode        (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btcodec       (char *output, size_t len, int argc, char *argv[]);//crms00232879 David MA
extern size_t CMD_btstate       (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btinquiry     (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btpair        (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btunpair      (char *output, size_t len, int argc, char *argv[]);//crms00207183 David MA
extern size_t CMD_btaddr        (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btid         (char *output, size_t len, int argc, char *argv[]); //crms00152015 Vivien ZHU
extern size_t CMD_bthloadver    (char *output, size_t len, int argc, char *argv[]); //crms00246578 David MA
//extern size_t CMD_btdownloader  (char *output, size_t len, int argc, char *argv[]);
//extern size_t CMD_dfuupgrade    (char *output, size_t len, int argc, char *argv[]);//#261837 wenfangw
extern size_t CMD_btcontinuoustx(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btcontinuousrx(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btpackettxrx(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btloopback(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_bthfplayback(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btavplayback(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btphoneconnect(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btphonedisconnect(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btlinkkey(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btreconnectsmartphonesetting(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btcallid(char * output,size_t len,int argc,char * argv [ ]);
extern size_t CMD_btafh(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btenablesniffmode(char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_bttestmode(char *output, size_t len, int argc, char *argv[]);

extern size_t CMD_btEnableBeacon(char *output, size_t len, int argc, char *argv[]);

#if defined(_NO_ICT_MODULE_)//crms00207635 David MA
extern size_t CMD_btradio       (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btstats       (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btbccmd  (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btinfo  (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btscomode     (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btvset        (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btreadafhmap  (char *output, size_t len, int argc, char *argv[]);
extern size_t CMD_btdownloadall (char *output, size_t len, int argc, char *argv[]);
#endif
/*!
 * \brief   Register all commands will call to cmd_regiter
 *
 */
void register_all(void)
{
    cmd_register( "help"        , CMD_help         , ACCESS_USR );
    cmd_register( "bth"         , CMD_bth          , ACCESS_USR );
    cmd_register( "btmode"      , CMD_btmode       , ACCESS_USR );
	
    cmd_register( "btenablebeacon"      , CMD_btEnableBeacon       , ACCESS_USR );

#if defined(_NO_ICT_MODULE_)//crms00207635 David MA
    cmd_register( "btradio"     , CMD_btradio      , ACCESS_USR );
    cmd_register( "btstats"     , CMD_btstats      , ACCESS_USR );
    cmd_register( "btscomode"   , CMD_btscomode    , ACCESS_USR );
    cmd_register( "btvset"      , CMD_btvset       , ACCESS_USR );
#ifdef ictouch
    cmd_register( "btreadafhmap", CMD_btreadafhmap , ACCESS_USR );
#endif
    //cmd_register( "btdownloader", CMD_btdownloader , ACCESS_USR );//crms00213064 David MA
    cmd_register( "btdownloadall", CMD_btdownloadall , ACCESS_USR );
//crms00152015 Vivien ZHU+
    cmd_register( "btbccmd"  , CMD_btbccmd , ACCESS_USR );
//crms00152015 Vivien ZHU-
#endif//crms00207635 David MA
    cmd_register( "btcodec"     , CMD_btcodec      , ACCESS_USR );//crms00232879 David MA
    cmd_register( "btstate"     , CMD_btstate      , ACCESS_USR );
    cmd_register( "btinquiry"   , CMD_btinquiry    , ACCESS_USR );
    cmd_register( "btpair"      , CMD_btpair       , ACCESS_USR );
    cmd_register( "btunpair"    , CMD_btunpair     , ACCESS_USR );//crms00207183 David MA
    cmd_register( "btaddr"      , CMD_btaddr       , ACCESS_USR );
    cmd_register( "btid"       , CMD_btid        , ACCESS_USR ); //crms00152015 Vivien ZHU
    cmd_register( "bthloadver"  , CMD_bthloadver   , ACCESS_USR ); //crms00246578 David MA
    //cmd_register( "btdownloader", CMD_btdownloader , ACCESS_USR );//crms00213064 David MA
    //cmd_register( "btdfuupgrade"  , CMD_dfuupgrade , ACCESS_USR );//#261837 wenfangw
    
    cmd_register( "btconrx"  , CMD_btcontinuousrx, ACCESS_USR );
    cmd_register( "btcontx"  , CMD_btcontinuoustx , ACCESS_USR );	
    cmd_register( "btpackettxrx"  , CMD_btpackettxrx , ACCESS_USR );
	cmd_register( "btloopback"	,	CMD_btloopback , ACCESS_USR);		
	cmd_register( "bthfplayback" ,	CMD_bthfplayback , ACCESS_USR);
	cmd_register( "btavplayback" ,	CMD_btavplayback , ACCESS_USR);
	cmd_register( "btphoneconnect" ,	CMD_btphoneconnect , ACCESS_USR);	
	cmd_register( "btphonedisconnect" , CMD_btphonedisconnect , ACCESS_USR); 
	cmd_register( "btenablesniffmode" , CMD_btenablesniffmode , ACCESS_USR); 
    cmd_register( "bttestmode" , CMD_bttestmode , ACCESS_USR);
    cmd_register( "btlinkkey" , CMD_btlinkkey , ACCESS_USR);
    cmd_register( "btreconnectsmartphonesetting" , CMD_btreconnectsmartphonesetting , ACCESS_USR);
	cmd_register( "btcallid" , CMD_btcallid , ACCESS_USR);

    cmd_register( "btafh"     , CMD_btafh      , ACCESS_USR );
	
}

/** @} */ // end of group EmbeddedCommands

