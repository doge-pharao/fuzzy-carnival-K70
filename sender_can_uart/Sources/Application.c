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
		if (UART_RxBuff_NofElements() != 0) {
			// Rx --Recibe un caracter desde consola--
			// prepare frame
			Frame.MessageID = 0x70U; /* Set Tx ID value - standard */
			Frame.FrameType = LDD_CAN_DATA_FRAME; /* Specyfying type of Tx frame - Data frame */

			unsigned char ch;

			while (UART_RxBuff_NofElements() != 0) {
				int i = 0;

				while (UART_RxBuff_NofElements() != 0 && i < 8) {
					(void) UART_RxBuff_Get(&ch);
					txbuffer[i] = ch;
				}
				txbuffer[8] = '\0';

				Frame.Length = i + 1; /* Set number of bytes in data frame - 4B */
				Frame.Data = txbuffer; /* Set pointer to OutData buffer */

				canData.isSent = FALSE;
				Error = CAN1_SendFrame(canData.handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
				if (Error != ERR_OK) {
					break;   // break to error state
				}

				while (!canData.isSent);


				sprintf(serialMessage, "Message ID: %x, Data: <%s> Transmitted \r\n", Frame.MessageID, Frame.Data);
				SendString(serialMessage, &uartData);
			}

		}

	}
}
