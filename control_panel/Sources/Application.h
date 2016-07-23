#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"
#include "PE_LDD.h"

#define ORANGE_TOUCH 0x0
#define ORANGE_VALUE 0x1

#define YELLOW_TOUCH 0x1
#define YELLOW_VALUE 0x2

#define GREEN_TOUCH 0x2
#define GREEN_VALUE 0x4

#define BLUE_TOUCH 0x3
#define BLUE_VALUE 0x8

#define UPDATE_DONE 0x0
#define ADC_VALUE_UPDATED 0x1
#define LED_VALUE_UPDATED 0x2

typedef struct {
  LDD_TDeviceData *handle;  /* LDD device handle */
  volatile uint8_t isSent;  /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; 			/* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;

typedef struct {
  LDD_TDeviceData *handle;  /* LDD device handle */
  volatile uint8_t isSent;  /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; 			/* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} CAN_Desc;

typedef struct {
  LDD_TDeviceData *handle;  /* LDD device handle */
  void (*conversionDoneFunction)(uint16_t); /* callback to put received character into buffer */
} ADC_Desc;

void APP_Run(void);

void updateLedStatus(uint8_t event);
void updateConversionValue(uint16_t value);

#endif /* APPLICATION_H_ */
