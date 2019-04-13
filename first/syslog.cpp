/*!-----------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved           \n
 ------------------------------------------------------------------ \n
  Module :        Bluetooth                                         \n
  Project :       ICTouch                                           \n
 ------------------------------------------------------------------ \n
  \file     syslog.cpp
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Syslog oswrapper
  \feature  crms00152015
  \version  1.0

  History :                                                         \n
  create  : 07/01/2009                                              \n
  - 2009/11/09 Vivien ZHU
  crms00200402 Modify the logger method
  - 2009/12/14 David MA                                             \n
    crms00205297 Optimize log usage in btmgr.
  - 2011/07/18 Ben Hu                                                \n
    crms00327506 Log optimization in SHA components                  \n
 */
//crms00327506 Ben Hu +
/*------------------------------------------------------------------
 * System includes
 *------------------------------------------------------------------*/
#include <stdio.h>
#include <stdarg.h>
#include <sys/syslog.h>
#include <syslog.h>

/*------------------------------------------------------------------
 * Module includes
 *------------------------------------------------------------------*/
#if !defined(_NO_ICT_MODULE_)
#include <ICTLogger.h>
#include <LoggerList.h>
#endif

#include   "stdinc.h"


static void do_syslog (char *logstr, const char* full_name, int line_num,
                        unsigned int flux, const char *format, va_list args)
{
    char *p = logstr;

    if (logstr == NULL)
    {
        return;
    }
    
    if (flux == 4/*FLUX_AEC*/ )
    {
        p += sprintf(p, "AEC:");
    }
    
    if (full_name != NULL)
    {
        p += sprintf(p, "%s:%d ", full_name, line_num);
    }
    
    p += vsprintf(p, format, args);
}


extern "C" void logout(const char* full_name, int line_num,
             unsigned int flux, unsigned int grav, const char *format, ...)
	{
	
		char *pName = NULL;
		pName = strrchr(const_cast<char*>(full_name), '/');
		
#if !defined(_NO_ICT_MODULE_)
		switch(grav)
		{
			case 90/*LOG_FATAL*/:
				LOGGER_IF_EMERG
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';

					
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->emergency(logstr);
#else
					ictlogger()->emergency(logstr);
#endif
				}
				break;			  
			
			case 40/*LOG_ANOMALY*/:
				LOGGER_IF_ERROR 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->error(logstr);
#else
					ictlogger()->error(logstr);
#endif
				}
				break;			  
			
			case 30/*LOG_WARNING*/:
				LOGGER_IF_WARNING 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->warning(logstr);
#else
					ictlogger()->warning(logstr);
#endif
				}
				break;			  
			
			case 20/*LOG_NORMAL*/:
				LOGGER_IF_NOTICE 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->notice(logstr);
#else
					ictlogger()->notice(logstr);
#endif
				}
				break;
				
		   case 10/*LOG_VERBOSE*/:
				LOGGER_IF_INFO 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->info(logstr);
#else
					ictlogger()->info(logstr);
#endif
				}
				break;
				
			case 0/*LOG_DEBUG*/:
				LOGGER_IF_DEBUG 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->debug(logstr);
#else
					ictlogger()->debug(logstr);
#endif
				}
				break;
	
			 default:
				LOGGER_IF_WARNING 
				{
					char logstr[8192];
					va_list  args;
					
					logstr[0] = '\0';
								
					va_start (args, format);
					do_syslog (logstr, (pName == NULL) ? (full_name):(pName+1), line_num, flux, format, args);
					va_end (args);
#ifdef RANGE_80X8EE
					logger()->warning("Wrong log level!");
					logger()->warning(logstr);
#else
					ictlogger()->warning("Wrong log level!");
					ictlogger()->warning(logstr);
#endif
				}
				break;
		}	 
#else
		va_list  args;
		// router_send(flux, grav, buf);
	
		/// \todo: Check the gravity
	
		// log processing
		if ( (full_name != NULL) && (line_num != 0) )
			printf("%s:%d ", full_name, line_num);
		else if (full_name != NULL)
			printf("%s ", full_name);
	
		va_start(args, format);
		vprintf( format, args );
		va_end(args);
	
		printf("\n");
#endif
	}


void __syslog(const char* full_name, int line_num,
             unsigned int flux, unsigned int grav, const char *format, ...)
{
#if !defined(_NO_ICT_MODULE_)
    switch(grav)
    {
        case 90/*LOG_FATAL*/:
            LOGGER_IF_EMERG
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->emergency(logstr);
#else
				ictlogger()->emergency(logstr);
#endif

            }
            break;            
        
        case 40/*LOG_ANOMALY*/:
            LOGGER_IF_ERROR 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->error(logstr);
#else
				ictlogger()->error(logstr);
#endif

            }
            break;            
        
        case 30/*LOG_WARNING*/:
            LOGGER_IF_WARNING 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->warning(logstr);
#else
				ictlogger()->warning(logstr);
#endif

            }
            break;            
        
        case 20/*LOG_NORMAL*/:
            LOGGER_IF_NOTICE 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->notice(logstr);
#else
				ictlogger()->notice(logstr);
#endif
            }
            break;
            
       case 10/*LOG_VERBOSE*/:
            LOGGER_IF_INFO 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->info(logstr);
#else
				ictlogger()->info(logstr);
#endif
            }
            break;
            
        case 0/*LOG_DEBUG*/:
            LOGGER_IF_DEBUG 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->debug(logstr);
#else
				ictlogger()->debug(logstr);
#endif
            }
            break;

         default:
            LOGGER_IF_WARNING 
            {
                char logstr[8192];
                va_list  args;
                
                logstr[0] = '\0';
                            
                va_start (args, format);
                do_syslog (logstr, full_name, line_num, flux, format, args);
                va_end (args);
#ifdef RANGE_80X8EE
                logger()->warning("Wrong log level!");
                logger()->warning(logstr);
#else
				ictlogger()->warning("Wrong log level!");
				ictlogger()->warning(logstr);
#endif
            }
            break;
    }    
#else
    va_list  args;
    // router_send(flux, grav, buf);

    /// \todo: Check the gravity

    // log processing
    if ( (full_name != NULL) && (line_num != 0) )
        printf("%s:%d ", full_name, line_num);
    else if (full_name != NULL)
        printf("%s ", full_name);

    va_start(args, format);
    vprintf( format, args );
    va_end(args);

    printf("\n");
#endif
}

void syslogtxt(unsigned int flux, unsigned int grav, const char *txt)
{
#if !defined(_NO_ICT_MODULE_)

    __syslog(NULL, 0, flux, grav, "%s", txt);

#else
    /// \todo: Check the gravity

    if ( flux == 4/*FLUX_AEC*/ ) {
        printf("AEC: %s", txt);
    }
    else
        printf(txt);
    printf("\n");

#endif

    return;
}




