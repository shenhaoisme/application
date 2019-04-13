/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     shell.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Shell header file
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
-------------------------------------------------------------------- */

/** @defgroup group2 Shell
 *  This is the group of Shell
 *  @{
 */

#ifndef _SHELL_H_
#define _SHELL_H_

/*!
 * \def SHELL_OUTPUT_BUFFER_LEN
 *      output buffer size control
 */
#  define SHELL_OUTPUT_BUFFER_LEN   (1024 * 4)

/*!
 * \def SHELL_INPUT_BUFFER_LEN
 *      input buffer size control
 */
#  define SHELL_INPUT_BUFFER_LEN    (1024 * 1)

/*!
 * \def CMD_OK()
 *      "<command_name> OK"
 */
#define CMD_OK()                             \
{                                            \
    p += sprintf(p, "%s OK", argv[0]);       \
    if ( (size_t)(p - output) > len - 32 ) {                        \
        syslog(__FILE__, __LINE__, FLUX_BT, LOG_ANOMALY,         \
            "CMD_OK: Risk of Overflow in output buffer : len = %d", \
            (size_t)(p - output) );                                 \
    }                                        \
    return (size_t)(p - output);             \
}

/*!
 * \def CMD_KO()
 *      "<command_name> KO"
 */
#define CMD_KO()                             \
{                                            \
    p += sprintf(p, "%s KO", argv[0]);       \
    if ( (size_t)(p - output) > len - 32 ) {                        \
        syslog(__FILE__, __LINE__, FLUX_BT, LOG_ANOMALY,         \
            "CMD_KO: Risk of Overflow in output buffer : len = %d", \
            (size_t)(p - output) );                                 \
    }                                        \
    return (size_t)(p - output);             \
}

/*!
 * \def CMD_HELP(s)
 *      "<command_name> <helpstring>"
 */
#define CMD_HELP(s)                          \
{                                            \
    p += sprintf(p, "%-14s %s", argv[0], s); \
    return (size_t)(p - output);             \
}

/*!
  \enum shell_access_type_t
  The Type of Shell Access Levels
 */
typedef enum
{
    ACCESS_USR   ,  //!< User Level Full Access
    ACCESS_LTD   ,  //!< User Level Limited Access
    ACCESS_DEV   ,  //!< Only Available for Development Version
    ACCESS_UNLOCK   //!< Only Available for Unlocked Terminal
} shell_access_type_t;


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
extern bool_t shell_access(
    shell_access_type_t access_type
    );

/*!
 * \brief Send Shell Command into Message Queue of Shell
 *      adds a command for execution.
 *
 * \param cmd   : Shell Command String
 */
extern void shell_queue_command(char *cmd);



/*!
 * \brief Shell Module Initialization and Starts
 *      It register all embedded commands and create the Shell thread.
 *
 */
extern void init_shell(void);

/*!
 * \brief Terminate Shell Module
 *
 */
extern void shell_term();


#endif /* _SHELL_H_ */

/** @} */ // end of group Shell

