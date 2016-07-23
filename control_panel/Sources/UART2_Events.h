/* ###################################################################
**     Filename    : UART2_Events.h
**     Project     : sender_can_uart
**     Processor   : MK70FN1M0VMJ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-16, 00:08, # CodeGen: 5
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         AS1_OnBlockReceived - void AS1_OnBlockReceived(LDD_TUserData *UserDataPtr);
**         AS1_OnBlockSent     - void AS1_OnBlockSent(LDD_TUserData *UserDataPtr);
**
** ###################################################################*/
/*!
** @file UART2_Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup UART2_Events_module UART2_Events module documentation
**  @{
*/         

#ifndef __UART2_Events_H
#define __UART2_Events_H
/* MODULE UART2_Events */

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
#include "AD1.h"

#ifdef __cplusplus
extern "C" {
#endif 

/*
** ===================================================================
**     Event       :  AS1_OnBlockReceived (module UART2_Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called when the requested number of data is
**         moved to the input buffer.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockReceived(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  AS1_OnBlockSent (module UART2_Events)
**
**     Component   :  AS1 [Serial_LDD]
*/
/*!
**     @brief
**         This event is called after the last character from the
**         output buffer is moved to the transmitter. 
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void AS1_OnBlockSent(LDD_TUserData *UserDataPtr);


/* END UART2_Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __UART2_Events_H*/
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
