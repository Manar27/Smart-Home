/*
 * UART_Register.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Manar
 */

#ifndef MCAL_UART_HEADER_UART_REGISTER_H_
#define MCAL_UART_HEADER_UART_REGISTER_H_

/*Half TX and RX Buffer to Transmit or Receive Data*/
#define UART_UDR 	(*(volatile u8*)0x2C)

/*-----------------------------------------------------------------------------*/
#define UART_UCSRA 	(*(volatile u8*)0x2B)
/*Receive Complete Flag*/
#define UART_RXC	7
/*Transmit Complete Flag*/
#define UART_TXC	6
/*Data Register Empty*/
#define UART_UDRE	5
/*Frame Error*/
#define UART_FE		4
/*Data OverRun*/
#define UART_DOR	3
/*Parity Error*/
#define UART_PE		2
/*Double Transmission Speed*/
#define UART_U2X	1
/*Multiprocessor Communication Mode*/
#define UART_MPCM	0

/*-----------------------------------------------------------------------------*/
#define UART_UCSRB 	(*(volatile u8*)0x2A)
/*RX Complete Interrupt Enable*/
#define UART_RXCIE	7
/*TX Complete Interrupt Enable*/
#define UART_TXCIE	6
/*Data Register Empty Interrupt Enable*/
#define UART_UDRIE	5
/*Receiver Enable*/
#define UART_RXEN	4
/*Transmitter Enable*/
#define UART_TXEN	3
/*Character Size*/
#define UART_UCSZ2	2
/*Receive Data Bit 8*/
#define UART_RXB8	1
/*Transmit Data Bit 8*/
#define UART_TXB8	0

/*-----------------------------------------------------------------------------*/
#define UART_UCSRC 	(*(volatile u8*)0x40)
/*Register Select -> UCSRC or UBRRH*/
#define UART_URSEL	7
/*UART select Mode -> 0 Asynchronous , 1 Synchronous*/
#define UART_UMSEL	6
/*Parity Moods Enable or disable*/
#define UART_UPM1	5
#define UART_UPM0	4
/*Stop bit select*/
#define UART_USBS	3
/*Character Size*/
#define UART_UCSZ1	2
#define UART_UCSZ0	1
/*Clock Polarity -> in Sync mode*/
#define UART_UCPOL	0

/*-----------------------------------------------------------------------------*/
/*Baud Rate*/
#define UART_UBRRL 	(*(volatile u8*)0x29)
#define UART_UBRRH 	(*(volatile u8*)0x40)


#endif /* MCAL_UART_HEADER_UART_REGISTER_H_ */
