#include "Application.h"
#include "AS1.h"

static UART_Desc uartData;
static CAN_Desc canData;

uint8_t rxbuffer; /* Initialization of output data buffer */
uint8_t txbuffer[9];
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
	// Init UART Devie
	uartData.handle = AS1_Init(&uartData);
	uartData.isSent = FALSE;
	uartData.rxChar = '\0';
	uartData.rxPutFct = UART_RxBuff_Put;

	// Init CAN Device
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
	Init();
	SendString((unsigned char*) "Press the keys to send.\r\n", &uartData);
	char serialMessage[50];
	char buffMsg[17];

	LDD_CAN_TErrorCounter errorCounterRX, oldErrCounterRX;
	LDD_CAN_TErrorCounter errorCounterTX, oldErrCounterTX;
	LDD_TError Error;

	for (;;) {
		if (canData.errorMask != CAN_NO_ERROR) {
			sprintf(serialMessage, "-------- ERROR BEGIN --------\r\n");
			SendString(serialMessage, &uartData);

			errorCounterRX = CAN1_GetReceiveErrorCounter(canData.handle);
			errorCounterTX = CAN1_GetTransmitErrorCounter(canData.handle);
			if (errorCounterRX != oldErrCounterRX
					|| errorCounterTX != oldErrCounterTX) {
				oldErrCounterRX = errorCounterRX;
				oldErrCounterTX = errorCounterTX;

				sprintf(serialMessage, "Error counters. RX:%u TX:%u\r\n",
						errorCounterRX, errorCounterTX);
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_BIT0_ERROR) {
				sprintf(serialMessage, "Bit0 error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_BIT1_ERROR) {
				sprintf(serialMessage, "Bit1 error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_ACK_ERROR) {
				sprintf(serialMessage, "knowledge error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_CRC_ERROR) {
				sprintf(serialMessage,
						"Cyclic redundancy check error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_FORM_ERROR) {
				sprintf(serialMessage,
						"Message form error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			if (canData.errorMask && LDD_CAN_STUFFING_ERROR) {
				sprintf(serialMessage, "Bit stuff error detect error mask\r\n");
				SendString(serialMessage, &uartData);
			}

			sprintf(serialMessage, " --------- ERROR END ---------\r\n");
			SendString(serialMessage, &uartData);

			canData.errorMask = CAN_NO_ERROR;

		} else {
			if (UART_RxBuff_NofElements() != 0) {
				// Rx - Receive a single character from UART -
				// prepare frame
				Frame.MessageID = 0x70U; 				/* Set Tx ID value - standard */
				Frame.FrameType = LDD_CAN_DATA_FRAME; 	/* Specyfying type of Tx frame - Data frame */

				unsigned char ch;

				while (UART_RxBuff_NofElements() != 0) {
					int i = 0;

					while (UART_RxBuff_NofElements() != 0 && i < 8) {
						(void) UART_RxBuff_Get(&ch);
						txbuffer[i] = ch;
					}
					txbuffer[8] = '\0';

					Frame.Length = i + 1; 	/* Set number of bytes in data frame - 4B */
					Frame.Data = txbuffer; 	/* Set pointer to OutData buffer */

					canData.isSent = FALSE;
					Error = CAN1_SendFrame(canData.handle, 1U, &Frame); /* Sends the data frame over buffer 0 */
					if (Error != ERR_OK) {
						sprintf(serialMessage,
								"-ERROR- Message ID: %x, couldn't be transmitted \r\n",
								Frame.MessageID);
						break;   // break to error state
					} else {
						while (!canData.isSent
								&& canData.errorMask == CAN_NO_ERROR)
							;

						if (canData.errorMask == CAN_NO_ERROR) {
							buffMsg[0] = '\0';
							char i = 0, offset = 0;
							for (; i < Frame.Length; i++) {
								switch (Frame.Data[i]) {
								case '\r':
									buffMsg[i + offset] = '\\';
									buffMsg[i + offset + 1] = 'r';
									offset++;
									break;
								case '\n':
									buffMsg[i + offset] = '\\';
									buffMsg[i + offset + 1] = 'n';
									offset++;
									break;
								default:
									buffMsg[i + offset] = Frame.Data[i];
									break;
								}
							}
							buffMsg[i + offset] = '\0';

							sprintf(serialMessage,
									"Message ID: %x, Data: <%s> Transmitted \r\n",
									Frame.MessageID, (char *) buffMsg);
						}
					}

					SendString(serialMessage, &uartData);
				}

			}
		}

	}
}
