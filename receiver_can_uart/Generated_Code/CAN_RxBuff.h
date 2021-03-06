/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CAN_RxBuff.h
**     Project     : receiver_can_uart
**     Processor   : MK70FN1M0VMJ12
**     Component   : RingBuffer
**     Version     : Component 01.046, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-07-16, 21:01, # CodeGen: 1
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : CAN_RxBuff
**          SDK                                            : KSDK1
**          Reentrant                                      : yes
**          Critical Section                               : CS2
**          Buffer Size                                    : 64
**          Element Size                                   : 1 Byte
**     Contents    :
**         Clear           - void CAN_RxBuff_Clear(void);
**         Put             - uint8_t CAN_RxBuff_Put(CAN_RxBuff_ElementType elem);
**         Putn            - uint8_t CAN_RxBuff_Putn(CAN_RxBuff_ElementType *elem, CAN_RxBuff_BufSizeType...
**         Get             - uint8_t CAN_RxBuff_Get(CAN_RxBuff_ElementType *elemP);
**         Peek            - uint8_t CAN_RxBuff_Peek(CAN_RxBuff_BufSizeType index, CAN_RxBuff_ElementType...
**         Compare         - uint8_t CAN_RxBuff_Compare(CAN_RxBuff_BufSizeType index,...
**         Delete          - uint8_t CAN_RxBuff_Delete(void);
**         NofElements     - CAN_RxBuff_BufSizeType CAN_RxBuff_NofElements(void);
**         NofFreeElements - CAN_RxBuff_BufSizeType CAN_RxBuff_NofFreeElements(void);
**         Deinit          - void CAN_RxBuff_Deinit(void);
**         Init            - void CAN_RxBuff_Init(void);
**
**     License   :  Open Source (LGPL)
**     Copyright : (c) Copyright Erich Styger, 2014-2015, all rights reserved.
**     Web: http://www.mcuoneclipse.com
**     This an open source software of an embedded component for Processor Expert.
**     This is a free software and is opened for education,  research  and commercial developments under license policy of following terms:
**     * This is a free software and there is NO WARRANTY.
**     * No restriction on use. You can use, modify and redistribute it for personal, non-profit or commercial product UNDER YOUR RESPONSIBILITY.
**     * Redistributions of source code must retain the above copyright notice.
** ###################################################################*/
/*!
** @file CAN_RxBuff.h
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup CAN_RxBuff_module CAN_RxBuff module documentation
**  @{
*/         

#ifndef __CAN_RxBuff_H
#define __CAN_RxBuff_H

/* MODULE CAN_RxBuff. */
#include "KSDK1.h"
#include "CS2.h"

#if KSDK1_SDK_VERSION_USED == KSDK1_SDK_VERSION_NONE
/* Include shared modules, which are used for whole project */
  #include "PE_Types.h"
  #include "PE_Error.h"
  #include "PE_Const.h"
  #include "IO_Map.h"
/* Include inherited beans */
  #include "Cpu.h"
#endif

#define CAN_RxBuff_BUF_SIZE    64   /* number of elements in the buffer */
#define CAN_RxBuff_ELEM_SIZE   1  /* size of a single element in bytes */
#define CAN_RxBuff_IS_REENTRANT   1  /* 1: Critical section used for accessing shared data, 0 otherwise */
#if CAN_RxBuff_ELEM_SIZE==1
  typedef uint8_t CAN_RxBuff_ElementType; /* type of single element */
#elif CAN_RxBuff_ELEM_SIZE==2
  typedef uint16_t CAN_RxBuff_ElementType; /* type of single element */
#elif CAN_RxBuff_ELEM_SIZE==4
  typedef uint32_t CAN_RxBuff_ElementType; /* type of single element */
#else
  #error "illegal element type size in properties"
#endif
#if CAN_RxBuff_BUF_SIZE<256
  typedef uint8_t CAN_RxBuff_BufSizeType; /* up to 255 elements (index 0x00..0xff) */
#else
  typedef uint16_t CAN_RxBuff_BufSizeType; /* more than 255 elements, up to 2^16 */
#endif

uint8_t CAN_RxBuff_Put(CAN_RxBuff_ElementType elem);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t CAN_RxBuff_Get(CAN_RxBuff_ElementType *elemP);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Get (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

CAN_RxBuff_BufSizeType CAN_RxBuff_NofElements(void);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void CAN_RxBuff_Init(void);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

CAN_RxBuff_BufSizeType CAN_RxBuff_NofFreeElements(void);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/

void CAN_RxBuff_Clear(void);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t CAN_RxBuff_Peek(CAN_RxBuff_BufSizeType index, CAN_RxBuff_ElementType *elemP);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Peek (component RingBuffer)
**     Description :
**         Returns an element of the buffer without removiing it.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to where to store the received
**                           element
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

#define CAN_RxBuff_Deinit() \
   /* nothing to deinitialize */
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Deinit (component RingBuffer)
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

uint8_t CAN_RxBuff_Delete(void);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Delete (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t CAN_RxBuff_Putn(CAN_RxBuff_ElementType *elem, CAN_RxBuff_BufSizeType nof);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Putn (component RingBuffer)
**     Description :
**         Put a number new element into the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * elem            - Pointer to new elements to be put into
**                           the buffer
**         nof             - number of elements
**     Returns     :
**         ---             - Error code
** ===================================================================
*/

uint8_t CAN_RxBuff_Compare(CAN_RxBuff_BufSizeType index, CAN_RxBuff_ElementType *elemP, CAN_RxBuff_BufSizeType nof);
/*
** ===================================================================
**     Method      :  CAN_RxBuff_Compare (component RingBuffer)
**     Description :
**         Compares the elements in the buffer.
**     Parameters  :
**         NAME            - DESCRIPTION
**         index           - Index of element. 0 peeks the top
**                           element, 1 the next, and so on.
**       * elemP           - Pointer to elements to compare with
**         nof             - number of elements to compare
**     Returns     :
**         ---             - zero if elements are the same, -1 otherwise
** ===================================================================
*/

/* END CAN_RxBuff. */

#endif
/* ifndef __CAN_RxBuff_H */
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
