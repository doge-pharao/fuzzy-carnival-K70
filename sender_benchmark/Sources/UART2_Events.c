/* ###################################################################
**     Filename    : UART2_Events.c
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
** @file UART2_Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup UART2_Events_module UART2_Events module documentation
**  @{
*/         
/* MODULE UART2_Events */

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
void AS1_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
  UART_Desc *ptr = (UART_Desc*)UserDataPtr;

  (void)AS1_ReceiveBlock(ptr->handle, (LDD_TData *)&ptr->rxChar, sizeof(ptr->rxChar));
  (void)ptr->rxPutFct(ptr->rxChar); /* but received character into buffer */
}

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
void AS1_OnBlockSent(LDD_TUserData *UserDataPtr)
{
	  UART_Desc *ptr = (UART_Desc*)UserDataPtr;

	  ptr->isSent = TRUE; /* set flag so sender knows we have finished */
}

/* END UART2_Events */

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
