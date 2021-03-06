#include "Application.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;

volatile bool DataFrameTxFlg;
volatile bool DataFrameRxFlg = FALSE;

LDD_TError Error;
LDD_CAN_TFrame Frame;

static void SendChar(unsigned char ch, UART_Desc *desc) {
	/* this will be set to 1 once the block has been sent */
	desc->isSent = FALSE;

	/* Send char */
	while (AS1_SendBlock(desc->handle, (LDD_TData*) &ch, 1) != ERR_OK) {
	}

	/* wait until we get the green flag from the TX UART interrupt */
	while (!desc->isSent) {
	}
}

static void SendString(const unsigned char *str, UART_Desc *desc) {
	while (*str != '\0') {
		SendChar(*str++, desc);
	}
}

static void Init(void) {
	// UART Initialization
	uartData.handle = AS1_Init(&uartData);
	uartData.isSent = FALSE;
	uartData.rxChar = '\0';
	uartData.rxPutFct = UART_RxBuff_Put;

	// CAN Initialization
	canData.handle = CAN1_Init(&canData);
	canData.isSent = FALSE;
	canData.rxPutFct = CAN_RxBuff_Put;

	/* set up to receive RX into input buffer */
	UART_RxBuff_Init(); /* initialize RX buffer assigned to the UART module */
	CAN_RxBuff_Init(); 	/* initialize RX buffer assigned to the CAN moduel */

	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while (AS1_ReceiveBlock(uartData.handle, (LDD_TData *) &uartData.rxChar,
			sizeof(uartData.rxChar)) != ERR_OK) {
	} /* initial kick off for receiving data */
}

void APP_Run(void) {
	Init();
	SendString((unsigned char*) "Hello World!\r\n", &uartData);

	for (;;) {
		if (UART_RxBuff_NofElements() != 0) {

			while (UART_RxBuff_NofElements() != 0) {
				unsigned char ch;
				uint8_t length = 0;
				unsigned char txbuffer[8];

				// Rx Receives a character from the console.
				while (UART_RxBuff_NofElements() != 0 && length < 8) {
					(void) UART_RxBuff_Get(&ch);
					txbuffer[length] = ch;
					length++;
				}

				// Prepare frame
				Frame.MessageID = 0x70U; 				/* Set Tx ID value - standard */
				Frame.FrameType = LDD_CAN_DATA_FRAME; 	/* Specyfying type of Tx frame - Data frame */
				Frame.Length = length; 		/* Set number of bytes in data frame - 4B */
				Frame.Data = (uint8_t *) &txbuffer; 				/* Set pointer to OutData buffer */

				canData.isSent = FALSE;
				Error = CAN1_SendFrame(canData.handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
				if (Error != ERR_OK) {
					break;   // break to error state
				}

				// Wait the completion of the transmission.
				while (!canData.isSent);
			}
		}

		if (CAN_RxBuff_NofElements()) {
			while (CAN_RxBuff_NofElements()) {
					unsigned char ch;

					//receive frame (buffer 0)
					CAN_RxBuff_Get(&ch);

					if (ch == '\r') {
						SendChar(ch, &uartData);
						SendChar('\n', &uartData);
					}
					else
						// Send the echo to the console.
						SendChar(ch, &uartData);
				}
		}
	}
}
