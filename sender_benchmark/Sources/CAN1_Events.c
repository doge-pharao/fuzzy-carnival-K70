/* ###################################################################
**     Filename    : CAN1_Events.c
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
** @file CAN1_Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup CAN1_Events_module CAN1_Events module documentation
**  @{
*/         
/* MODULE CAN1_Events */

#include "Cpu.h"
#include "Events.h"
#include "Timer1_Events.h"
#include "UART2_Events.h"
#include "CAN1_Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

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
void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
	  CAN_Desc *ptr = (CAN_Desc*)UserDataPtr;

	  ptr->isSent = TRUE; /* set flag so sender knows we have finished */
}
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
void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex BufferIdx)
{
	 LDD_CAN_TFrame Frame;
	 CAN_Desc *ptr = (CAN_Desc*)UserDataPtr;

	 (void)CAN1_ReadFrame(ptr->handle, 0U, &Frame);
	 ptr->rxChar = *Frame.Data;
	 (void)ptr->rxPutFct(ptr->rxChar); /* but received character into buffer */
}

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
void CAN1_OnTransmitWarning(LDD_TUserData *UserDataPtr)
{
  /* Write your code here ... */
}

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
void CAN1_OnBusOff(LDD_TUserData *UserDataPtr)
{
	LDD_CAN_TErrorMask errorMask;
	CAN_Desc * ptr = (CAN_Desc *) UserDataPtr;

	CAN1_GetError(ptr->handle, &errorMask);
	ptr->errorMask = errorMask;
}

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
void CAN1_OnError(LDD_TUserData *UserDataPtr)
{
	LDD_CAN_TErrorMask errorMask;
	CAN_Desc * ptr = (CAN_Desc *) UserDataPtr;

	CAN1_GetError(ptr->handle, &errorMask);
	ptr->errorMask = errorMask;
}

/* END CAN1_Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

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
