/* ###################################################################
**     Filename    : ADC_Events.c
**     Project     : control_panel
**     Processor   : MK70FN1M0VMJ12
**     Component   : Events
**     Version     : Driver 01.00
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-23, 00:24, # CodeGen: 3
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Contents    :
**         AD1_OnMeasurementComplete - void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr);
**
** ###################################################################*/
/*!
** @file ADC_Events.c
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup ADC_Events_module ADC_Events module documentation
**  @{
*/         
/* MODULE ADC_Events */

#include "Cpu.h"
#include "Events.h"
#include "Timer1_Events.h"
#include "UART2_Events.h"
#include "CAN1_Events.h"
#include "TSS_Events.h"
#include "ADC_Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */
#include "Application.h"
/*
** ===================================================================
**     Event       :  AD1_OnMeasurementComplete (module ADC_Events)
**
**     Component   :  AD1 [ADC_LDD]
*/
/*!
**     @brief
**         Called after measurement is done, [Interrupt service/event]
**         is enabled, OnMeasurementComplete event is enabled and ADC
**         device is enabled. See [SetEventMask()] method or [Event
**         mask] property group to enable this event and [Enable]
**         method or [Enabled in init. code] property to enable ADC
**         device. If DMA is enabled , this event is called after the
**         configured number of measurements and DMA transfer is done.
**     @param
**         UserDataPtr     - Pointer to the user or
**                           RTOS specific data. The pointer is passed
**                           as the parameter of Init method. 
*/
/* ===================================================================*/
void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr)
{
	uint16_t buffer;
	ADC_Desc *ptr = (ADC_Desc*)UserDataPtr;
	AD1_GetMeasuredValues(ptr->handle, &buffer);

	updateConversionValue(buffer);
}

/* END ADC_Events */

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
