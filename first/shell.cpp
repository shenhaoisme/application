/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
  ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
  ------------------------------------------------------------------ \n
  \file     shell.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Shell Source File
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
  - 2009/12/14 David MA                                             \n
  crms00205297 Optimize log usage in btmgr.
  - 2010/11/30 David MA
  Wrk(crms00277198),Cr(crms00275916) VHE[BT] Sometimes,Bluetooth goes out of working \n
 - 2011/03/08 Terry Zhao
    Wrk(crms00299420),Cr(crms00259958) VHE[BT-regression]:Sometime, BT process go to die
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
#include "id.h"
#include "primitive.h"
#include "os_wrapper.h"
#include "mem_wrapper.h"

/** @defgroup group2 Shell
 *  This is the group of Shell
 *  @{
 */

/*------------------------------------------------------------------
 * Module Macro and Type definitions
 *------------------------------------------------------------------*/


/*------------------------------------------------------------------
 * Module External functions Definitions
 *------------------------------------------------------------------*/

/*!
 * \brief Shell Access Authentication
 *
 * \param access_type
 *              - ACCESS_USR    :
 *              - ACCESS_LTD    :
 *              - ACCESS_DEV    :
 *              - ACCESS_UNLOCK :
 *
 * \return bool_t
 *              - true : Granted Access
 *              - false: Rejected Access
 */
bool_t shell_access(shell_access_type_t access_type)
{
    bool_t b_granted = FALSE;

    switch(access_type) {
    case ACCESS_USR   :
        // always
        b_granted = TRUE;
        break;

    case ACCESS_LTD   :
        // TODO: What is the limited condition ?
        if (is_release_version()){
            //b_granted = ;
        }
        else{
            b_granted = TRUE;
        }
        break;

    case ACCESS_DEV   :
        // only with development versions
        if ( FALSE == is_release_version() )
            b_granted = TRUE;
        break;

    case ACCESS_UNLOCK:
        // only if lock is not set
        b_granted = TRUE;
        /// \todo: How to get the lock information ?
        //b_granted = ;
        break;
    }

    return b_granted;
}

#if 0
/*!
 * \brief Send Shell Command into Message Queue of Shell
 *      adds a command for execution.
 *
 * \param cmd   : Shell Command String
 */
void shell_queue_command(char *cmd)
{
    msg_t       msg ;
    uint32_t    length = 0;

    if (cmd == NULL) {
        return;
    }

    length = strlen(cmd);
    msg.payload = pw_malloc(length+1);
    if ( msg.payload != NULL) {
        memcpy( msg.payload, cmd, length+1 );
        msg.payload_length = length;

        msg.primitiveCode = ePRIM_SHELL_IN;
        msg.src_component = eCOMPONENT_CLI;
        msg.dst_component = eCOMPONENT_SHELL;

        msgQ_send(QUEUE_ID_shell, msg);
    }
}
#endif



/*-----------------------------------------------------------------------------
  shell thread entry point
  ---------------------------------------------------------------------------*/

/*!
 *  \brief This is the structure of shell command output .
 */
typedef struct {
    char dummy;      ///< used for (OPCODE)
    char buff[SHELL_OUTPUT_BUFFER_LEN];  ///< Shell Command Output Buffer
    char crlf[2];    ///< used for (CR & LF)
} shell_output_t;

#if defined(_NO_ICT_MODULE_)
/*!
 * \brief Shell Thread Entry Point Function
 *      It is pending at a message queue, if any shell command is received, it execute
 *      this command and log out the command execution result.
 */
static void shell_thread_entry(void)
{
    size_t  len;
    static  shell_output_t shell_output;

    for(;;)
    {
        msg_t         msg ;

        msgQ_recv(QUEUE_ID_shell, msg);

        memset(shell_output.buff, 0, SHELL_OUTPUT_BUFFER_LEN);
        len = shell_exec(
            (const char *)msg.payload,  // command
            shell_output.buff,          // Shell output buffer
            SHELL_OUTPUT_BUFFER_LEN     // Length of output buffer
            );
        if (len > 0)
        {
            syslogtxt(FLUX_SHELL, LOG_NORMAL, shell_output.buff);//crms00152015 David MA
        }
        pw_free(msg.payload);
    }
}


#endif

extern void register_all(void);

/*!
 * \brief Shell Module Initialization and Starts
 *      It register all embedded commands and create the Shell thread.
 *
 */
void init_shell()
{
    register_all();
#if defined(_NO_ICT_MODULE_)    //crms00275916 David MA
    thread_create(THREAD_ID_shell, shell_thread_entry);
#endif    //crms00275916 David MA
}

/*!
 * \brief Terminate Shell Module
 *
 */
void shell_term()
{
#if defined(_NO_ICT_MODULE_)    //crms00275916 David MA
    thread_delete(THREAD_ID_shell);
#endif    //crms00275916 David MA
    cmd_unregister_all();
}

/** @} */ // end of group Shell

