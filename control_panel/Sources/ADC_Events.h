/* ###################################################################
**     Filename    : ADC_Events.h
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
** @file ADC_Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup ADC_Events_module ADC_Events module documentation
**  @{
*/         

#ifndef __ADC_Events_H
#define __ADC_Events_H
/* MODULE ADC_Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "TU1.h"
#include "GREENLED.h"
#include "AS1.h"
#include "CAN1.h"
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
void AD1_OnMeasurementComplete(LDD_TUserData *UserDataPtr);


/* END ADC_Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __ADC_Events_H*/
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
