/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : UART_RxBuff.c
**     Project     : sender_can_uart_K70
**     Processor   : MK70FN1M0VMJ15
**     Component   : RingBuffer
**     Version     : Component 01.046, Driver 01.00, CPU db: 3.00.000
**     Repository  : My Components
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-06-25, 19:36, # CodeGen: 0
**     Abstract    :
**         This component implements a ring buffer for different integer data type.
**     Settings    :
**          Component name                                 : UART_RxBuff
**          SDK                                            : KSDK1
**          Reentrant                                      : yes
**          Critical Section                               : CS1
**          Buffer Size                                    : 64
**          Element Size                                   : 1 Byte
**     Contents    :
**         Clear           - void UART_RxBuff_Clear(void);
**         Put             - uint8_t UART_RxBuff_Put(UART_RxBuff_ElementType elem);
**         Putn            - uint8_t UART_RxBuff_Putn(UART_RxBuff_ElementType *elem,...
**         Get             - uint8_t UART_RxBuff_Get(UART_RxBuff_ElementType *elemP);
**         Peek            - uint8_t UART_RxBuff_Peek(UART_RxBuff_BufSizeType index,...
**         Compare         - uint8_t UART_RxBuff_Compare(UART_RxBuff_BufSizeType index,...
**         Delete          - uint8_t UART_RxBuff_Delete(void);
**         NofElements     - UART_RxBuff_BufSizeType UART_RxBuff_NofElements(void);
**         NofFreeElements - UART_RxBuff_BufSizeType UART_RxBuff_NofFreeElements(void);
**         Deinit          - void UART_RxBuff_Deinit(void);
**         Init            - void UART_RxBuff_Init(void);
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
** @file UART_RxBuff.c
** @version 01.00
** @brief
**         This component implements a ring buffer for different integer data type.
*/         
/*!
**  @addtogroup UART_RxBuff_module UART_RxBuff module documentation
**  @{
*/         

/* MODULE UART_RxBuff. */

#include "UART_RxBuff.h"

#if UART_RxBuff_IS_REENTRANT
  #define UART_RxBuff_DEFINE_CRITICAL() CS1_CriticalVariable()
  #define UART_RxBuff_ENTER_CRITICAL()  CS1_EnterCritical()
  #define UART_RxBuff_EXIT_CRITICAL()   CS1_ExitCritical()
#else
  #define UART_RxBuff_DEFINE_CRITICAL() /* nothing */
  #define UART_RxBuff_ENTER_CRITICAL()  /* nothing */
  #define UART_RxBuff_EXIT_CRITICAL()   /* nothing */
#endif
static UART_RxBuff_ElementType UART_RxBuff_buffer[UART_RxBuff_BUF_SIZE]; /* ring buffer */
static UART_RxBuff_BufSizeType UART_RxBuff_inIdx;  /* input index */
static UART_RxBuff_BufSizeType UART_RxBuff_outIdx; /* output index */
static UART_RxBuff_BufSizeType UART_RxBuff_inSize; /* size data in buffer */
/*
** ===================================================================
**     Method      :  UART_RxBuff_Put (component RingBuffer)
**     Description :
**         Puts a new element into the buffer
**     Parameters  :
**         NAME            - DESCRIPTION
**         elem            - New element to be put into the buffer
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t UART_RxBuff_Put(UART_RxBuff_ElementType elem)
{
  uint8_t res = ERR_OK;
  UART_RxBuff_DEFINE_CRITICAL();

  UART_RxBuff_ENTER_CRITICAL();
  if (UART_RxBuff_inSize==UART_RxBuff_BUF_SIZE) {
    res = ERR_TXFULL;
  } else {
    UART_RxBuff_buffer[UART_RxBuff_inIdx] = elem;
    UART_RxBuff_inIdx++;
    if (UART_RxBuff_inIdx==UART_RxBuff_BUF_SIZE) {
      UART_RxBuff_inIdx = 0;
    }
    UART_RxBuff_inSize++;
  }
  UART_RxBuff_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Putn (component RingBuffer)
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
uint8_t UART_RxBuff_Putn(UART_RxBuff_ElementType *elem, UART_RxBuff_BufSizeType nof)
{
  uint8_t res = ERR_OK;

  while(nof>0) {
    res = UART_RxBuff_Put(*elem);
    if (res!=ERR_OK) {
      break;
    }
    elem++; nof--;
  }
  return res;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Get (component RingBuffer)
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
uint8_t UART_RxBuff_Get(UART_RxBuff_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  UART_RxBuff_DEFINE_CRITICAL();

  UART_RxBuff_ENTER_CRITICAL();
  if (UART_RxBuff_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    *elemP = UART_RxBuff_buffer[UART_RxBuff_outIdx];
    UART_RxBuff_inSize--;
    UART_RxBuff_outIdx++;
    if (UART_RxBuff_outIdx==UART_RxBuff_BUF_SIZE) {
      UART_RxBuff_outIdx = 0;
    }
  }
  UART_RxBuff_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_NofElements (component RingBuffer)
**     Description :
**         Returns the actual number of elements in the buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
UART_RxBuff_BufSizeType UART_RxBuff_NofElements(void)
{
  return UART_RxBuff_inSize;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_NofFreeElements (component RingBuffer)
**     Description :
**         Returns the actual number of free elements/space in the
**         buffer.
**     Parameters  : None
**     Returns     :
**         ---             - Number of elements in the buffer.
** ===================================================================
*/
UART_RxBuff_BufSizeType UART_RxBuff_NofFreeElements(void)
{
  return (UART_RxBuff_BufSizeType)(UART_RxBuff_BUF_SIZE-UART_RxBuff_inSize);
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Init (component RingBuffer)
**     Description :
**         Initializes the data structure
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_RxBuff_Init(void)
{
  UART_RxBuff_inIdx = 0;
  UART_RxBuff_outIdx = 0;
  UART_RxBuff_inSize = 0;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Clear (component RingBuffer)
**     Description :
**         Clear (empty) the ring buffer.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void UART_RxBuff_Clear(void)
{
  UART_RxBuff_DEFINE_CRITICAL();

  UART_RxBuff_ENTER_CRITICAL();
  UART_RxBuff_Init();
  UART_RxBuff_EXIT_CRITICAL();
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Peek (component RingBuffer)
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
uint8_t UART_RxBuff_Peek(UART_RxBuff_BufSizeType index, UART_RxBuff_ElementType *elemP)
{
  uint8_t res = ERR_OK;
  int idx; /* index inside ring buffer */
  UART_RxBuff_DEFINE_CRITICAL();

  UART_RxBuff_ENTER_CRITICAL();
  if (index>=UART_RxBuff_BUF_SIZE) {
    res = ERR_OVERFLOW; /* asking for an element outside of ring buffer size */
  } else if (index<UART_RxBuff_inSize) {
    idx = (UART_RxBuff_outIdx+index)%UART_RxBuff_BUF_SIZE;
    *elemP = UART_RxBuff_buffer[idx];
  } else { /* asking for an element which does not exist */
    res = ERR_RXEMPTY;
  }
  UART_RxBuff_EXIT_CRITICAL();
  return res;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Compare (component RingBuffer)
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
uint8_t UART_RxBuff_Compare(UART_RxBuff_BufSizeType index, UART_RxBuff_ElementType *elemP, UART_RxBuff_BufSizeType nof)
{
  uint8_t cmpResult = 0;
  uint8_t res;
  UART_RxBuff_ElementType val;

  while(nof>0) {
    res = UART_RxBuff_Peek(index, &val);
    if (res!=ERR_OK) { /* general failure? */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    if (val!=*elemP) { /* mismatch */
      cmpResult = (uint8_t)-1; /* no match */
      break;
    }
    elemP++; index++; nof--;
  }

  return cmpResult;
}

/*
** ===================================================================
**     Method      :  UART_RxBuff_Deinit (component RingBuffer)
**     Description :
**         Driver de-initialization
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
/**
void UART_RxBuff_Deinit(void)
{
  ** Function is implemented as macro in the header file
}
*/
/*
** ===================================================================
**     Method      :  UART_RxBuff_Delete (component RingBuffer)
**     Description :
**         Removes an element from the buffer
**     Parameters  : None
**     Returns     :
**         ---             - Error code
** ===================================================================
*/
uint8_t UART_RxBuff_Delete(void)
{
  uint8_t res = ERR_OK;
  UART_RxBuff_DEFINE_CRITICAL();

  UART_RxBuff_ENTER_CRITICAL();
  if (UART_RxBuff_inSize==0) {
    res = ERR_RXEMPTY;
  } else {
    UART_RxBuff_inSize--;
    UART_RxBuff_outIdx++;
    if (UART_RxBuff_outIdx==UART_RxBuff_BUF_SIZE) {
      UART_RxBuff_outIdx = 0;
    }
  }
  UART_RxBuff_EXIT_CRITICAL();
  return res;
}

/* END UART_RxBuff. */

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