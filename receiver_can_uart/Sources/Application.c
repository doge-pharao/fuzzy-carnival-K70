#include "Application.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;

volatile bool DataFrameTxFlg;
volatile bool DataFrameRxFlg = FALSE;

uint8_t rxbuffer[8]; /* Initialization of output data buffer */
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

static void Init(void) {
	Frame.Data = rxbuffer; /* Set pointer to OutData buffer */

	// Inicializacion UART
	uartData.handle = AS1_Init(&uartData);
	uartData.isSent = FALSE;

	canData.handle = CAN1_Init(&canData);
	canData.isSent = FALSE;
	canData.rxChar = '\0';
	canData.rxPutFct = CAN_RxBuff_Put;

	/* set up to receive RX into input buffer */
	CAN_RxBuff_Init(); /* initialize RX buffer */

}

void APP_Run(void) {
	Init();
	SendString((unsigned char*) "Hello World\r\n", &uartData);
	DataFrameRxFlg = FALSE;
	DataFrameTxFlg = FALSE;

	for (;;) {

		while (CAN_RxBuff_NofElements()) {
			unsigned char ch;
			//receive frame (buffer 0)
			CAN_RxBuff_Get(&ch);

			SendString((unsigned char*) "Message ID: 0x70, Data: <", &uartData);
			switch(ch) {
				case '\r':
					SendString((unsigned char*) "\\r", &uartData);
					break;
				case '\n':
					SendString((unsigned char*) "\\n", &uartData);
					break;
				default:
					// Send the echo to the console.
					SendChar(ch, &uartData);
			}
			SendString((unsigned char*) "> received\r\n", &uartData);
		}

	}
}
