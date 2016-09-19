#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"
#include "PE_LDD.h"
#include <stdio.h>

#define CAN_NO_ERROR 0x00
#define CAN_ERROR 0x10
#define CAN_BUSS_OFF 0x20

typedef struct {
  LDD_TDeviceData *handle;  /* LDD device handle */
  volatile uint8_t isSent;  /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; 			/* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;

typedef struct {
  LDD_TDeviceData *handle;  /* LDD device handle */
  volatile uint8_t isSent;  /* this will be set to 1 once the block has been sent */
  volatile LDD_CAN_TErrorMask errorMask;
  uint8_t rxChar; 			/* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} CAN_Desc;

void APP_Run(void);

#endif /* APPLICATION_H_ */
