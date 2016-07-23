/* ###################################################################
**     Filename    : TSS_Events.h
**     Project     : control_panel
**     Processor   : MK70FN1M0VMJ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-22, 21:01, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         TSS1_fOnFault   - void TSS1_fOnFault(byte u8FaultElecNum);
**         TSS1_fOnInit    - void TSS1_fOnInit(void);
**         TSS1_fCallBack0 - void TSS1_fCallBack0(TSS_CONTROL_ID u8ControlId);
**
** ###################################################################*/
/*!
** @file TSS_Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup TSS_Events_module TSS_Events module documentation
**  @{
*/         

#ifndef __TSS_Events_H
#define __TSS_Events_H
/* MODULE TSS_Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "TU1.h"
#include "GREENLED.h"
#include "AS1.h"
#include "UART_RxBuff.h"
#include "CAN1.h"
#include "CAN_RxBuff.h"
#include "CS1.h"
#include "KSDK1.h"
#include "CS2.h"
#include "ORANGELED.h"
#include "BLUELED.h"
#include "YELLOWLED.h"
#include "TSS1.h"

#ifdef __cplusplus
extern "C" {
#endif 

void TSS1_fOnFault(byte u8FaultElecNum);
/*
** ===================================================================
**     Event       :  TSS1_fOnFault (module TSS_Events)
**
**     Component   :  TSS1 [TSS_Library]
**     Description :
**         This callback function is called by TSS after Fault
**         occurence. This event is enabled always and depends on
**         selection 'generate code' if the callback is used.
**         The default CallBack Name is automatically generated with
**         automatic prefix update by current Component Name. User can
**         define own name, but then the automatic name update is not
**         functional.
**         Option is available from TSS3.0 version.
**     Parameters  :
**         NAME            - DESCRIPTION
**         u8FaultElecNum  - The value defines
**                           electrode number on which measurement fault
**                           occured.
**     Returns     : Nothing
** ===================================================================
*/

void TSS1_fOnInit(void);
/*
** ===================================================================
**     Event       :  TSS1_fOnInit (module TSS_Events)
**
**     Component   :  TSS1 [TSS_Library]
**     Description :
**         This callback function is automatically called during the
**         TSS Init function execution. The function is intended for
**         implementation of peripherals initialization. TSS Component
**         automatically enables clock for all used TSS peripherals in
**         the internal function TSS_InitDevices which is called by
**         this callback.
**         This event is enabled always and depends on selection
**         'generate code' if the callback is used.
**         The default CallBack Name is automatically generated with
**         automatic prefix update by current Component Name. User can
**         define own name, but then the automatic name update is not
**         functional.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void TSS1_fCallBack0(TSS_CONTROL_ID u8ControlId);
/*
** ===================================================================
**     Event       :  TSS1_fCallBack0 (module TSS_Events)
**
**     Component   :  TSS1 [TSS_Library]
**     Description :
**         Callback definition for Control 0. This event is enabled
**         only if Control 0 is enabled.
**         The default CallBack Name is automatically generated with
**         automatic prefix update by current Component Name. User can
**         define own name, but then the automatic name update is not
**         functional.
**     Parameters  :
**         NAME            - DESCRIPTION
**         u8ControlId     - Valid unique Identifier of
**                           the Control which generated the CallBack
**                           function. This Id can be used for finding
**                           of Callback's source Control.
**     Returns     : Nothing
** ===================================================================
*/


/* END TSS_Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __TSS_Events_H*/
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.5 [05.21]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
