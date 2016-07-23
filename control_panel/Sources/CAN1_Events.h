/* ###################################################################
**     Filename    : CAN1_Events.h
**     Project     : sender_can_uart
**     Processor   : MK70FN1M0VMJ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-15, 22:32, # CodeGen: 2
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         CAN1_OnFreeTxBuffer    - void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex...
**         CAN1_OnFullRxBuffer    - void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex...
**         CAN1_OnTransmitWarning - void CAN1_OnTransmitWarning(LDD_TUserData *UserDataPtr);
**         CAN1_OnReceiveWarning  - void CAN1_OnReceiveWarning(LDD_TUserData *UserDataPtr);
**         CAN1_OnBusOff          - void CAN1_OnBusOff(LDD_TUserData *UserDataPtr);
**         CAN1_OnError           - void CAN1_OnError(LDD_TUserData *UserDataPtr);
**
** ###################################################################*/
/*!
** @file CAN1_Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup CAN1_Events_module CAN1_Events module documentation
**  @{
*/         

#ifndef __CAN1_Events_H
#define __CAN1_Events_H
/* MODULE CAN1_Events */

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

/*
** ===================================================================
**     Event       :  CAN1_OnFreeTxBuffer (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is empty after a
**         successful transmit of a message. This event is available
**         only if method SendFrame is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Receive message buffer index.
*/
/* ===================================================================*/
void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  CAN1_OnFullRxBuffer (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the buffer is full after a
**         successful receive a message. This event is available only
**         if method ReadFrame or SetRxBufferState is enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
**     @param
**         BufferIdx       - Transmit buffer index.
*/
/* ===================================================================*/
void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx);

/*
** ===================================================================
**     Event       :  CAN1_OnTransmitWarning (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the CAN controller goes into
**         warning status due to the transmit error counter exceeding
**         96 and neither an error status nor a BusOff status are
**         present. This event is available only if method SendFrame is
**         enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CAN1_OnTransmitWarning(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  CAN1_OnReceiveWarning (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the CAN controller goes into a
**         warning status due to the receive error counter exceeding 96
**         and neither an error status nor a BusOff status are present.
**         The event is available only if Interrupt service/event is
**         enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CAN1_OnReceiveWarning(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  CAN1_OnBusOff (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when the node status becomes bus-off.
**         The event is available only if Interrupt service/event is
**         enabled.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CAN1_OnBusOff(LDD_TUserData *UserDataPtr);

/*
** ===================================================================
**     Event       :  CAN1_OnError (module CAN1_Events)
**
**     Component   :  CAN1 [CAN_LDD]
*/
/*!
**     @brief
**         This event is called when a channel error (not the error
**         returned by a given method) occurs.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. This pointer is passed
**                           as the parameter of Init method.
*/
/* ===================================================================*/
void CAN1_OnError(LDD_TUserData *UserDataPtr);


/* END CAN1_Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __CAN1_Events_H*/
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
