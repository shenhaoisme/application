/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     shell_exec.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA,Viven ZHU
  \brief    Shell Execute Header File
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
-------------------------------------------------------------------- */

/** @defgroup group2 Shell
 *  This is the group of Shell
 *  @{
 */

#ifndef _SHELL_EXEC_H_
#define _SHELL_EXEC_H_


/*!
 * \brief Execute Shell Command
 *
 * \param input		: command input string
 * \param output	: the buffer for command output
 * \param len		: the length of this output buffer
 *
 * \return size_t	: the length of output string
 */
extern size_t shell_exec(
    const char *input_buf, char *output_buf, size_t len
    );



/*!
 * \brief Register a command into commands list.
 *
 * \param cmd_name	:	The name of this command
 * \param command	:	The entry point function pointer of this command
 * \param access_type	: command access level
 *
 * \return bool_t	: true if success, false in failure.
 */
extern bool_t __cmd_register(
    const char          *cmd_name   , void * (*command)(void),
    shell_access_type_t  access_type
    );

/*! Creates a type name for this function type */
typedef void *(f2reg)(void);

/*!
 * \def cmd_register(name, cmd, access_type)
 *		Define cmd_register as __cmd_register.
 */
#define cmd_register(name, cmd           , access_type) \
      __cmd_register(name, (f2reg *)(cmd), access_type)


/*!
 * \brief Unregister a command. Remove it from registered commands list.
 *
 * \param cmd_name	: the name of this command
 *
 * \return bool_t	: true if success, false in failure.
 */
extern bool_t cmd_unregister(const char *cmd_name);

/*!
 * \brief Unregister all commands. Remove them from registered commands list.
 *
 */
extern void cmd_unregister_all(void);

#endif /* _SHELL_EXEC_H_ */

/** @} */ // end of group Shell

