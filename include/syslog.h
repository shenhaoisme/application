/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     syslog.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Syslog Header File
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
  - 2009/12/14 David MA                                             \n
    crms00205297 Optimize log usage in btmgr.
  - 2011/07/18 Ben Hu                                                \n
    crms00327506 Log optimization in SHA components                  \n
 */
//crms00327506 Ben Hu +
#ifndef _SYS_SYSLOG_H
#define _SYS_SYSLOG_H


/*!
  \enum log_flux_t
  The Log Source Module IDs
 */
#define FLUX_MAIN   0   //!< Main Routine Log
#define FLUX_SHELL  1   //!< Shell Module Log
#define FLUX_RTP    2   //!< RTP Module Log
#define FLUX_AUDIO  3   //!< Audio Related Log
#define FLUX_AEC    4   //!< AEC Related Log
#if !defined(DEVICE_BT)
#define FLUX_SIZE   5
#else
#define FLUX_BT	    5
#define FLUX_BTHCI  6
#define FLUX_BTSTACK 7
#define FLUX_BTMON  8
#define FLUX_SIZE   9
#endif



/*!
  \enum log_grav_t
  The Log Severity Levels
 */
#define LOG_FATAL		90		//!< fatal exception
#define LOG_ANOMALY		40		//!< errors and critical errors only 
#define LOG_WARNING		30		//!< abnormal situation no consequences on service // crms00152017 Bruce.Zhang
#define LOG_NORMAL		20		//!< level used in release version
#define LOG_VERBOSE		10		//!< level used in development version
#define LOG_DEBUG		0		//!< level reserved to developer

/*!
 * \brief syslog wrapper function.
 *       outputs the specified string to the specified destination flow.
 *       - if enabled, a timestamp is added
 *       - the output buffer length is limited to SYSLOG_OUTPUT_BUFFER_LEN
 *
 * \param full_name : source file name in which this function is called
 * \param line_num  : source file line number in which this function is called
 * \param flux		: syslog source module
 * \param grav		: severity level of log
 * \param format	: output format
 */
#define syslog __syslog

extern void __syslog(const char* full_name, int line_num, unsigned int flux, unsigned int grav, const char *format, ...);

extern void logout(const char* full_name, int line_num, unsigned int flux, unsigned int grav, const char *format, ...);

/*!
 * \brief syslog wrapper function for simple string output.
 *        outputs the specified string to the specified destination flow.
 *
 * \param flux		: syslog source module
 * \param grav		: severity level of log
 * \param txt		: output string
 */
extern void syslogtxt(
             unsigned int flux, unsigned int grav, const char *txt);

#endif /* _SYSLOG_H_ */
//crms00327506 Ben Hu -
