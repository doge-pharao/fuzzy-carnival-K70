#include "Application.h"
#include "AD1.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;
static ADC_Desc adcData;

static void SendString(const char *str, UART_Desc *desc);
void sendLedStatusByCAN(CAN_Desc* canData, uint8_t status);
void sendLedStatusByUART(UART_Desc* uartDesc, uint8_t status);
void sendConversionByUART(UART_Desc* uartDesc, uint16_t value);
void sendConversionByCAN(CAN_Desc* canDesc, uint16_t value);


static void Init(void) {
	// Inicializacion UART
	uartData.handle = AS1_Init(&uartData);
	uartData.isSent = FALSE;
	uartData.rxChar = '\0';
	uartData.rxPutFct = UART_RxBuff_Put;

	canData.handle = CAN1_Init(&canData);
	canData.isSent = FALSE;
	canData.errorMask = CAN_NO_ERROR;

	adcData.handle = AD1_Init(&adcData);
	adcData.conversionDoneFunction = updateConversionValue;
	AD1_CreateSampleGroup(adcData.handle, (LDD_ADC_TSample*) NULL, 1);

	LDD_TDeviceData* myTimer = TU1_Init(&adcData);
	TU1_Enable(myTimer);

	/* set up to receive RX into input buffer */
	UART_RxBuff_Init(); /* initialize RX buffer */

	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while (AS1_ReceiveBlock(uartData.handle, (LDD_TData *) &uartData.rxChar,
			sizeof(uartData.rxChar)) != ERR_OK) {
	} /* initial kick off for receiving data */

}


uint8_t PANEL_EVENT= UPDATE_DONE;
uint16_t adcValue = 0x0000;
uint8_t led_status = 0x00;

void APP_Run(void) {
	Init();
	sendLedStatusByCAN(&canData, led_status);
	SendString((char *) "Press the keys to send.\r\n", &uartData);

	char serialMessage[50];
	LDD_CAN_TErrorCounter errorCounterRX, oldErrCounterRX;
	LDD_CAN_TErrorCounter errorCounterTX, oldErrCounterTX;

	for (;;) {
		if (canData.errorMask != CAN_NO_ERROR) {
			SendString("-------- ERROR BEGIN --------\r\n", &uartData);

			errorCounterRX = CAN1_GetReceiveErrorCounter(canData.handle);
			errorCounterTX = CAN1_GetTransmitErrorCounter(canData.handle);
			if (errorCounterRX != oldErrCounterRX
					|| errorCounterTX != oldErrCounterTX) {
				oldErrCounterRX = errorCounterRX;
				oldErrCounterTX = errorCounterTX;

				sprintf((char *)serialMessage, "Error counters. RX:%u TX:%u\r\n",
						errorCounterRX, errorCounterTX);
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_BIT0_ERROR) {
				sprintf((char *)serialMessage, "Bit0 error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_BIT1_ERROR) {
				sprintf((char *)serialMessage, "Bit1 error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_ACK_ERROR) {
				sprintf((char *)serialMessage, "knowledge error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_CRC_ERROR) {
				sprintf((char *)serialMessage, "Cyclic redundancy check error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_FORM_ERROR) {
				sprintf((char *)serialMessage, "Message form error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_STUFFING_ERROR) {
				sprintf((char *)serialMessage, "Bit stuff error detect error mask\r\n");
				SendString((char *)serialMessage, &uartData);
			}

			sprintf((char *)serialMessage, " --------- ERROR END ---------\r\n");
			SendString((char *)serialMessage, &uartData);

			canData.errorMask = CAN_NO_ERROR;

		} else {
		switch(PANEL_EVENT) {
			case ADC_VALUE_UPDATED:
				sendConversionByUART(&uartData, adcValue);
				sendConversionByCAN(&canData, adcValue);
				PANEL_EVENT = UPDATE_DONE;
				break;

			case LED_VALUE_UPDATED:
				sendLedStatusByCAN(&canData, led_status);
				sendLedStatusByUART(&uartData, led_status);
				PANEL_EVENT= UPDATE_DONE;
				break;

			default:
				TSS_Task();
				break;
		}
		}
	}

}

uint8_t rxbuffer; /* Initialization of output data buffer */
uint8_t txbuffer[9];
LDD_TError Error;




void updateConversionValue(uint16_t value) {
	adcValue = value;
	PANEL_EVENT = ADC_VALUE_UPDATED;
}

void updateLedStatus(uint8_t event){
	switch(event) {
		case ORANGE_TOUCH:
			ORANGELED_NegVal(ORANGELED_DeviceData);
			led_status = led_status ^ ORANGE_VALUE;
			break;
		case YELLOW_TOUCH:
			YELLOWLED_NegVal(YELLOWLED_DeviceData);
			led_status = led_status ^ YELLOW_VALUE;
			break;
		case GREEN_TOUCH:
			GREENLED_NegVal(GREENLED_DeviceData);
			led_status = led_status ^ GREEN_VALUE;
			break;
		case BLUE_TOUCH:
			BLUELED_NegVal(BLUELED_DeviceData);
			led_status = led_status ^ BLUE_VALUE;
			break;
		default:
			break;
	}

	PANEL_EVENT = LED_VALUE_UPDATED;
}

void sendLedStatusByCAN(CAN_Desc* canData, uint8_t status){
	static LDD_CAN_TFrame Frame;

	Frame.MessageID = 0x70U; 				/* Set Tx ID value - standard */
	Frame.FrameType = LDD_CAN_DATA_FRAME; 	/* Specyfying type of Tx frame - Data frame */
	Frame.Length =sizeof(status); 			/* Set number of bytes in data frame - 4B */
	Frame.Data = &status; 					/* Set pointer to OutData buffer */

	canData->isSent = FALSE;
	Error = CAN1_SendFrame(canData->handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
	while(!canData->isSent && canData->errorMask == CAN_NO_ERROR);
}

void sendLedStatusByUART(UART_Desc* uartDesc, uint8_t status){
	char message[50];
	char *orangeStatus=(status & ORANGE_VALUE)?"ON":"OFF";
	char *yellowStatus=(status & YELLOW_VALUE)?"ON":"OFF";
	char *greenStatus=(status & GREEN_VALUE)?"ON":"OFF";
	char *blueStatus=(status & BLUE_VALUE)?"ON":"OFF";

	sprintf((char *)message, "Led status: ORANGE:%s YELLOW:%s GREEN:%s BLUE:%s\r\n",
			orangeStatus, yellowStatus, greenStatus, blueStatus);
	SendString((unsigned char*) message, uartDesc);
}



void sendConversionByUART(UART_Desc* uartDesc, uint16_t value){
	unsigned char message[50];

	sprintf((char *)message, "Current ADC value:%x\r\n", value);
	SendString((char *) message, uartDesc);
}

void sendConversionByCAN(CAN_Desc* canDesc, uint16_t value){
	static LDD_CAN_TFrame Frame;

	Frame.MessageID = 0x71U; 				/* Set Tx ID value - standard */
	Frame.FrameType = LDD_CAN_DATA_FRAME; 	/* Specyfying type of Tx frame - Data frame */
	Frame.Length =sizeof(value); 			/* Set number of bytes in data frame - 4B */
	Frame.Data = (uint8_t *) &value; 					/* Set pointer to OutData buffer */

	canDesc->isSent = FALSE;
	Error = CAN1_SendFrame(canDesc->handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
	while(!canDesc->isSent && canDesc->errorMask == CAN_NO_ERROR);
}

static void SendChar(char ch, UART_Desc *desc) {
	desc->isSent = FALSE;
	while (AS1_SendBlock(desc->handle, (LDD_TData*) &ch, 1) != ERR_OK) {
	} /* Send char */
	while(!desc->isSent);
}

static void SendString(const char *str, UART_Desc *desc) {
	while (*str != '\0') {
		SendChar(*str++, desc);
	}
}
