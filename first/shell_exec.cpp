/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
 ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
 ------------------------------------------------------------------ \n
  \file     shell_exec.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Shell Execute
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
 */

/*------------------------------------------------------------------
 * System includes
 *------------------------------------------------------------------*/

#include <unistd.h>
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

/** @defgroup group2 Shell
 *  This is the group of Shell
 *  @{
 */


/*!
 * \brief This is cmd_t structure.
 */
typedef struct
{
    shell_access_type_t  access_type;   //!< Command Access Level
    char                *cmd_name   ;   //!< Command Name
    union {
        void *  (*cmd )(void);          //!< Command Function Without Any Parameter
        size_t  (*scmd)(
            char *output, size_t len, int argc, char *argv[]
            );                  //!< Command Function With Parameters List
    } u;                    //!< Command Entry Point Function Pointer
} cmd_t;


/*!
 * \def HELP_CMD_STR
 *      It is the 'help' command string
 */
#define HELP_CMD_STR        "help"

/*!
 * \def COMMENT_CMD_STR
 *      It is command line indicator char.
 */
#define COMMENT_CMD_STR     "#"

/*!
 * \def CMD_MAX_ARGS
 *      Define maximum arguments number
 */
#define     CMD_MAX_ARGS            (64)

/*!
 * \def SHELL_MAX_REGISTERED
 * It is the maximum number commands that the application can register.
 */
#define     SHELL_MAX_REGISTERED    (160)

/*!
 * \brief A global value to save all the registered commands.
 *
 */
static cmd_t cmd_list[SHELL_MAX_REGISTERED];

/*!
 * \brief A global value to indicate if command is "help" command.
 *
 */
static bool_t cmdIsHelp = FALSE;

/*!
 * \brief Compare the name of 2 commands.
 *
 * \param a : pointer of command 'a'
 * \param b : pointer of command 'b'
 *
 * \return int
 *          - 0     : name is same
 *          - positive  : the name of a is greater than b's
 *          - negative  : the name of a is less than b's
 */
static int cmd_compare(const void *a, const void *b)
{
    char *nameA = ((const cmd_t *)a)->cmd_name;
    char *nameB = ((const cmd_t *)b)->cmd_name;
    int  result;

    if ((nameA != NULL) && (nameB != NULL))
        result = strcasecmp(nameA, nameB);
    else if ((nameA == NULL) && (nameB == NULL))
        result =  0;
    else if (nameA != NULL)
        result = -1;
    else
        result =  1;

    return result;
}


/*!
 * \brief Looking for and check if this shell input string is a registered command.
 *
 * \param cmd_name  : shell input string
 * \param cmd       : Get the command pointer if matched
 *
 * \return bool_t   : true if found. else false.
 */
static bool_t cmd_find(const char *cmd_name, cmd_t *cmd)
{
    int i;

    for(i = 0 ; (i < SHELL_MAX_REGISTERED) ; i++)
    {
    if (cmd_list[i].cmd_name != NULL)
    {
        if (strcasecmp(cmd_name, cmd_list[i].cmd_name) == 0)
        {
            memcpy(cmd, &cmd_list[i], sizeof(cmd_t));
            return TRUE;
        }
    }
    }
    return FALSE;
}


/*!
 * \brief Register a command into commands list.
 *
 * \param cmd_name  :   The name of this command
 * \param command   :   The entry point function pointer of this command
 * \param access_type   : command access level
 *
 * \return bool_t   : true if success, false in failure.
 */
bool_t __cmd_register(
    const char          *cmd_name   , void * (*command)(void),
    shell_access_type_t  access_type
    )
{
    if ((cmd_name != NULL) && (command != NULL))
    {
    int i     = 0;
    int found = FALSE;

    while(i < SHELL_MAX_REGISTERED)
    {
        found = (cmd_list[i].cmd_name == NULL);
        if (found)
        break;
        i++;
    }

    if (found)
    {
        cmd_list[i].access_type = access_type;
        cmd_list[i].cmd_name    = strdup(cmd_name);
        cmd_list[i].u.cmd       = command;
        qsort(cmd_list, SHELL_MAX_REGISTERED, sizeof(cmd_t), cmd_compare);
        return TRUE;
    }
    }
    return FALSE;
}


/*!
 * \brief Unregister a command. Remove it from registered commands list.
 *
 * \param cmd_name  : the name of this command
 *
 * \return bool_t   : true if success, false in failure.
 */
bool_t cmd_unregister(const char *cmd_name)
{
    if (cmd_name != NULL)
    {
        int i;

        for(i = 0 ; (i < SHELL_MAX_REGISTERED) ; i++)
        {
            if (cmd_list[i].cmd_name == NULL)
                continue;

            if (strcasecmp(cmd_name, cmd_list[i].cmd_name) == 0)
            {
                free(cmd_list[i].cmd_name);
                cmd_list[i].cmd_name = NULL;
                cmd_list[i].u.cmd    = NULL;
                qsort(cmd_list,SHELL_MAX_REGISTERED,sizeof(cmd_t),cmd_compare);
                return TRUE;
            }
        }
    }
    return FALSE;
}

/*!
 * \brief Unregister all commands. Remove them from registered commands list.
 *
 */
void cmd_unregister_all(void)
{
    int i;

    for(i = 0 ; (i < SHELL_MAX_REGISTERED) ; i++)
    {
        if (cmd_list[i].cmd_name == NULL)
            continue;

        free(cmd_list[i].cmd_name);
        cmd_list[i].cmd_name = NULL;
        cmd_list[i].u.cmd    = NULL;
    }
}

/*!
 * \brief Execute Shell Command
 *
 * \param input     : command input string
 * \param output    : the buffer for command output
 * \param len       : the length of this output buffer
 *
 * \return size_t   : the length of output string
 */
size_t shell_exec(const char *input, char *output, size_t len)
{
    int    outlen = 0;
    char  *buffer;              // work buffer (variable size ?)

    const char *sep = "\t\n\r ";// words separators
    char  *word;                // strtok_r result
    char  *brkt   = NULL;       // strtok_r working string

    cmd_t  cmd;                 // command
    int    argc   = 0;          // # parameters
    char  *argv[CMD_MAX_ARGS];  // parameters list (stack !)

    memset(argv, 0, CMD_MAX_ARGS * sizeof(char *));

    // make a copy of input_buf parameter
    buffer = strdup(input);

    // search for command
    word = strtok_r(buffer, sep, &brkt);
    if (word == NULL)
    {
        free(buffer);
        return 0;
    }

    // on elimine les lignes de commentaires.
    // on pourrait faire plus fin et eliminer les commentaires
    // partout sur la ligne...
    if (strcasecmp(word, COMMENT_CMD_STR) == 0)
    {
        free(buffer);
        return 0;
    }

    // try first to find the command
    if (! cmd_find(word, &cmd))
    {
        sprintf(output, "<%s> unknown/unregistered command\n", word);
        free(buffer);
        return strlen(output);
    }

    // and check if its a protected command
    if (! shell_access(cmd.access_type))
    {
        sprintf(output, "<%s> unknown/unregistered command\n", word);
        free(buffer);
        return strlen(output);
    }

    if (cmd.u.cmd != NULL)
    {
        // store command name in argv[0]
        argv[argc++] = cmd.cmd_name;

        // store command arguments in argv[]
        {
            for(;;)
            {
                word = strtok_r(NULL, sep, &brkt);
                if ((word != NULL) && (argc < CMD_MAX_ARGS))
                {
                    if (strcasecmp(word, COMMENT_CMD_STR) == 0)
                        break;
                    argv[argc++] = word;
                }
                else
                {
                    break;
                }
            }
        }

        // execute command
        {
            int l;

            if (! cmdIsHelp)
                l = sprintf(output, "#%s#\n", argv[0]);
            else
                l = 0;

            outlen = cmd.u.scmd(output+l, len-l, argc, argv);
            outlen += l;
        }

        if (cmdIsHelp)
        {
            // we always add a '\n' at the end if it is missing:
            if ((outlen >= 1) && (output[outlen-1] != '\n'))
            {
                output[outlen++]= '\n' ;
                output[outlen  ]= '\0' ;
            }
        }
    }
    else
    {
        sprintf(output, "<%s> cannot execute (NULL pointer)\n", word);
    }
    free(buffer);
    return outlen;
}

/*!
 * \brief The help command. To give all help information if no parameter,
 *  or give the help infomation for given command.
 *
 * \param output    : command output string
 * \param len       : length of output string
 * \param argc      : command parameters number
 * \param argv      : command parameters list
 *
 * \return size_t   : number of characters wrote in output buffer
 */
size_t CMD_help(char *output, size_t len, int argc, char *argv[])
{
  char  buf[64];
  char *p = output;

  switch(argc) {
    case 1:
    {
        int i = 0;
        int j = 0;

        cmdIsHelp = TRUE;

        for(i = 0, j = 0 ; (i < SHELL_MAX_REGISTERED) ; i++)
        {
            if (cmd_list[i].cmd_name == NULL)
                continue;

            if (shell_access(cmd_list[i].access_type))
            {
                sprintf(buf, "%s help", cmd_list[i].cmd_name);
                p += sprintf(p, "%3d ", j++);
                p += shell_exec(buf, p, len);
            }
        }
        cmdIsHelp = FALSE;
        CMD_OK();
    }
    case 2:
    {
        if (strcasecmp(argv[1], "help") != 0)
        {
            sprintf(buf, "%s help", argv[1]);

            p += shell_exec(buf, p, len);

            CMD_OK();
        }
        break;
    }
  }
  CMD_HELP("[help | <command_name>]");
}

/** @} */ // end of group Shell


