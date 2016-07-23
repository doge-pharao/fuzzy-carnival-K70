#include "Application.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;

uint8_t rxbuffer; /* Initialization of output data buffer */
uint8_t txbuffer[9];
LDD_TError Error;
LDD_CAN_TFrame Frame;

static void SendChar(unsigned char ch, UART_Desc *desc) {
	desc->isSent = FALSE; /* this will be set to 1 once the block has been sent */
	while (AS1_SendBlock(desc->handle, (LDD_TData*) &ch, 1) != ERR_OK) {
	} /* Send char */
	while (!desc->isSent) {
	} /* wait until we get the green flag from the TX interrupt */
}

static void SendString(const unsigned char *str, UART_Desc *desc) {
	while (*str != '\0') {
		SendChar(*str++, desc);
	}
}

uint8_t led_status = 0x00;
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

	sendLedStatusByCAN(canData, led_status);
	sendLedStatusByUART(uartData, led_status);
}

void sendLedStatusByCAN(CAN_Desc canData, uint8_t status){
	Frame.MessageID = 0x70U; 				/* Set Tx ID value - standard */
	Frame.FrameType = LDD_CAN_DATA_FRAME; 	/* Specyfying type of Tx frame - Data frame */
	Frame.Length =sizeof(status); 			/* Set number of bytes in data frame - 4B */
	Frame.Data = &status; 					/* Set pointer to OutData buffer */

	Error = CAN1_SendFrame(canData.handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
}

void sendLedStatusByUART(UART_Desc uartDesc, uint8_t status){
	unsigned char message[50];
	char *orangeStatus=(status & ORANGE_VALUE)?"ON":"OFF";
	char *yellowStatus=(status & YELLOW_VALUE)?"ON":"OFF";
	char *greenStatus=(status & GREEN_VALUE)?"ON":"OFF";
	char *blueStatus=(status & BLUE_VALUE)?"ON":"OFF";

	sprintf(message, "Led status: ORANGE:%s YELLOW:%s GREEN:%s BLUE:%s\r\n",
			orangeStatus, yellowStatus, greenStatus, blueStatus);
	SendString((unsigned char*) message, &uartData);
}

static void Init(void) {
	// Inicializacion UART
	uartData.handle = AS1_Init(&uartData);
	uartData.isSent = FALSE;
	uartData.rxChar = '\0';
	uartData.rxPutFct = UART_RxBuff_Put;

	canData.handle = CAN1_Init(&canData);
	canData.isSent = FALSE;

	/* set up to receive RX into input buffer */
	UART_RxBuff_Init(); /* initialize RX buffer */

	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while (AS1_ReceiveBlock(uartData.handle, (LDD_TData *) &uartData.rxChar,
			sizeof(uartData.rxChar)) != ERR_OK) {
	} /* initial kick off for receiving data */
}

void APP_Run(void) {
	Init();
	SendString((unsigned char*) "Press the keys to send.\r\n", &uartData);
	char serialMessage[50];

	for (;;) {
		TSS_Task();
	}

}
