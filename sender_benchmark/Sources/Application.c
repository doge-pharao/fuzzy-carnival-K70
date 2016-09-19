#include "Application.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;

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
	canData.errorMask = CAN_NO_ERROR;

	/* set up to receive RX into input buffer */
	UART_RxBuff_Init(); /* initialize RX buffer */

	/* Set up ReceiveBlock() with a single byte buffer. We will be called in OnBlockReceived() event. */
	while (AS1_ReceiveBlock(uartData.handle, (LDD_TData *) &uartData.rxChar,
			sizeof(uartData.rxChar)) != ERR_OK) {
	} /* initial kick off for receiving data */
}

void APP_Run(void) {
	LDD_TError Error;
	LDD_CAN_TFrame FramePing;
	unsigned char i = 0x00U;
	char serialMessage[50];
	char buffMsg[17];

	Init();

	SendString((unsigned char*) "Press the keys to send 100 messages.\r\n", &uartData);

	FramePing.MessageID = 0x20U; /* Set Tx ID value - standard */
	FramePing.FrameType = LDD_CAN_DATA_FRAME; /* Specyfying type of Tx frame - Data frame */
	FramePing.Length = 1; /* Set number of bytes in data frame - 4B */
	FramePing.Data = &i;

	for (;;) {

		if (UART_RxBuff_NofElements() != 0) {
			char ch;
			while (UART_RxBuff_NofElements() != 0) {
				(void) UART_RxBuff_Get(&ch);
			};

			SendString((unsigned char*) "Sending...\r\n", &uartData);

			for (i = 0;
					i < 100
					&& Error == ERR_OK
					&& canData.errorMask == CAN_NO_ERROR; i++) {

				canData.isSent = FALSE;

				do
					Error = CAN1_SendFrame(canData.handle, 1U, &FramePing);
				while(Error == ERR_BUSY);

				while (!canData.isSent && canData.errorMask == CAN_NO_ERROR && Error == ERR_OK)
					;

			}

			if (Error != ERR_OK) {
				sprintf(serialMessage,
						"-ERROR- Message ID: %x, couldn't be transmitted \r\n",
						FramePing.MessageID);
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask == CAN_NO_ERROR) {
				sprintf(serialMessage,
						"Message ID: %x, Data: <0x%d> Transmitted \r\n",
						FramePing.MessageID, *FramePing.Data);

				SendString(serialMessage, &uartData);
			}



			SendString((unsigned char*) "Done.\r\n", &uartData);
			SendString((unsigned char*) "Press the keys to send 100 messages.\r\n", &uartData);
		}
	}

}
