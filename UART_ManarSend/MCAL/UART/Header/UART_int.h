/*
 * UART_int.h
 *
 *  Created on: Sep 9, 2022
 *      Author: Dell
 */

#ifndef MCAL_UART_UART_INT_H_
#define MCAL_UART_UART_INT_H_


// CHECK ERROR STATUS //
typedef enum
{
	UART_OK,
	UART_NOK
}UART_tenuErrorStatus;


typedef struct
{
	u8 UART_u8ParityBits;
	u8 UART_u8PStopBit;
	u8 UART_u8DataBits;
	u8 UART_u8Mode;
	u16 UART_u16BaudRate;

}UART_tstrConfiguration;



//***************************************************** Mode Options ************************************************************
#define UART_u8_Transmite                      0x08
#define UART_u8_Recieve                        0x10
//*******************************************************************************************************************************


//***************************************************** Parity Bit Options ******************************************************
#define UART_u8_DISABLED_PARITY                0X00
#define UART_u8_EVEN_PARITY                    0X20
#define UART_u8_ODD_PARITY                     0X30
//*******************************************************************************************************************************



//**************************************************** Stop Bit Options *********************************************************
#define UART_u8_ONE_STOP_BIT                   0X00
#define UART_u8_TWO_STOP_BIT                   0X08
//*******************************************************************************************************************************



//**************************************************** Character Size Options ***************************************************
#define UART_u8_FIVE_DATA_BITS                 0X00
#define UART_u8_SIX_DATA_BITS                  0X02
#define UART_u8_SEVEN_DATA_BITS                0X04
#define UART_u8_EIGHT_DATA_BITS                0X06
#define UART_u8_NINE_DATA_BITS                 0X06
//*******************************************************************************************************************************


//**************************************************** Baud Rate Options ********************************************************
#define UART_u16_BAUD_RATE_2400                   416
#define UART_u16_BAUD_RATE_4800                   207
#define UART_u16_BAUD_RATE_9600                   103
#define UART_u16_BAUD_RATE_14_4K                  68
#define UART_u16_BAUD_RATE_19_2K                  51
#define UART_u16_BAUD_RATE_28_8K                  34
#define UART_u16_BAUD_RATE_38_4K                  25
#define UART_u16_BAUD_RATE_57_6K                  16
#define UART_u16_BAUD_RATE_76_8K                  12
#define UART_u16_BAUD_RATE_115_2k                 8
#define UART_u16_BAUD_RATE_230_4k                 3
#define UART_u16_BAUD_RATE_250k                   3
#define UART_u16_BAUD_RATE_0_5M                   1
#define UART_u16_BAUD_RATE_1M                     0
//*******************************************************************************************************************************

UART_tenuErrorStatus  UART_enuInit(UART_tstrConfiguration* Add_pstrConfigue);

UART_tenuErrorStatus  UART_enuInitRXInterrupt(UART_tstrConfiguration* Add_pstrConfigue);

UART_tenuErrorStatus  UART_enuTransmite(u16 Copy_pu16Data);

UART_tenuErrorStatus  UART_enuReceive(u8* Add_pu16Data);
void UART_CallBackFunctionRX(void (*PTF)(void));
void __vector_13(void)		__attribute__((signal));
#endif /* MCAL_UART_UART_INT_H_ */
