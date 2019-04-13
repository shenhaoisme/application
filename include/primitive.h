/*!------------------------------------------------------------------\n
  Copyright 1997-2009 Alcatel-Lucent. All Rights Reserved            \n
 ------------------------------------------------------------------- \n
  Module :        Bluetooth                                          \n
  Project :       ICTouch                                            \n
 ------------------------------------------------------------------- \n
  \file     primitive.h
  \ingroup  ICTModule
  \date     07/01/2009
  \author   David MA
  \brief    Primitive header file
  \feature  crms00152015                                             \n
  \version  1.0

  History :                                                          \n
  create  : 07/01/2009                                               \n
-------------------------------------------------------------------- */

#ifndef _PRIMITIVE_H_
#define _PRIMITIVE_H_


/*------------------------------------------------------------------
 * Macro and Type definitions
 *------------------------------------------------------------------*/


/*!
  \enum E_COMPONENT_ID
  sub-component ID - between sub-component, the communication will be primitive
 */
typedef enum
{
    eCOMPONENT_DBUS = 1,    //!< External Component

    eCOMPONENT_VMFSM,       //!< Voice Mode FSM Component
    eCOMPONENT_RTP,         //!< RTP Component
    eCOMPONENT_EPT,         //!< Endpoint Component

    eCOMPONENT_CLI,         //!< Command Line Component (Only for Unit Test)
    eCOMPONENT_SHELL,       //!< Audio Shell Component

    eCOMPONENT_MAX

} E_COMPONENT_ID;


/*!
 * \enum E_PRIMITIVE_CODE
 * primitive code - between sub-component, the communication will be primitive
 */
typedef enum {

    /// Unknown primitive
    ePRIM_CODE_UNKNOWN,

    /// primitve from D-Bus to VMFSM to control audio routing
    ePRIM_DBUS_CONTROL_VM           =  0x1000,

    /// voicemode FSM primitives
    ePRIM_VM_FSM                    =  0x2000,

    /// Shell command incoming message
    ePRIM_SHELL_IN                  =  0x3000,

    /// Shell output ougoing message
    ePRIM_SHELL_OUT                 =  0x4000,

	/// Endpoint Ring message
	ePRIM_EPT_RING                  =  0x5000,

    /// Endpoint DTMF message
    ePRIM_EPT_DTMF                  =  0x6000,

} E_PRIMITIVE_CODE;

/*!
 *  \brief This is a primitive structure.
 *
 * primitive structure
 *   1) primitive code
 *   2) source component
 *   3) destination component
 *   4) payload length
 *   5) payload
 *
 * NOTE: payload is depend on the primtive type (eCode)
 *       some of the payload structures are defined below
 */
typedef struct
{
    uint16_t    primitiveCode;  //!< E_PRIMITIVE_CODE
    uint8_t     src_component;  //!< E_COMPONENT_ID
    uint8_t     dst_component;  //!< E_COMPONENT_ID

    uint32_t    payload_length; //!< payload byte length
    void*       payload;        //!< payload pointer

} S_PRIMITIVE;


#endif // _PRIMITIVE_H_

