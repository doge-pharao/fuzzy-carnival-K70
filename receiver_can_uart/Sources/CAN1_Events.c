/* ###################################################################
**     Filename    : CAN1_Events.c
**     Project     : receiver_can_uart
**     Processor   : MK70FN1M0VMJ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-16, 21:01, # CodeGen: 1
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         CAN1_OnFreeTxBuffer - void CAN1_OnFreeTxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex...
**         CAN1_OnFullRxBuffer - void CAN1_OnFullRxBuffer(LDD_TUserData *UserDataPtr, LDD_CAN_TMBIndex...
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
#include "Timer_Events.h"
#include "USART2_Events.h"
#include "CAN1_Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"

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
	 uint8_t rxbuffer[8];
	 LDD_CAN_TFrame Frame;
	 Frame.Data = rxbuffer;

	 CAN_Desc *ptr = (CAN_Desc*)UserDataPtr;

	 (void)CAN1_ReadFrame(ptr->handle, 0U, &Frame);

	 for(int i = 0; i < Frame.Length; i++) {
		 (void)ptr->rxPutFct(Frame.Data[i]); /* but received character into buffer */
	 }
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
