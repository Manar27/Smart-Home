/*
 * UART_Prog.h
 *
 *  Created on: Sep 5, 2022
 *      Author: Manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/UART_Register.h"
#include "../Header/UART_Private.h"
#include "../Header/UART_Interface.h"


static void (*GPTF_RX) (void) = NULL;

UART_tenuErrorStatus UART_enuInit (UART_tstrConfiguration* Add_pstrConfigue)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;
	if(Add_pstrConfigue== NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
		/*Enable UCSRC -> URSEL = 1*/
		Set_Bit(UART_UCSRC, UART_URSEL);
		/*Set Parity bits*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8ParityBits;
		/*Set Stop bit*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8PStopBit;
		/*Check 9 bit*/
		if(Add_pstrConfigue->UART_u8DataBits == UART_u8_NINE_DATA_BITS)
		{
			UART_UCSRC |= 0x04;
		}
		/*Set Character Size*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8DataBits;
		/*Choose Transmit or Receive*/
		UART_UCSRB |= Add_pstrConfigue->UART_u8Mode;
		/*Enable UBRRH -> URSEL = 0*/
		clear_Bit(UART_UCSRC, UART_URSEL);
		/*Set Baud Rate*/
		UART_UBRRL |= (u8)(Add_pstrConfigue->UART_u16BaudRate);
		UART_UBRRH |= (u8)((Add_pstrConfigue->UART_u16BaudRate) >> 8);

	}
	return Local_enuErrorStatus;
}
UART_tenuErrorStatus UART_enuInitRXInterrupt (UART_tstrConfiguration* Add_pstrConfigue)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;

	if(Add_pstrConfigue== NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
		/*Enable UCSRC -> URSEL = 1*/
		Set_Bit(UART_UCSRC, UART_URSEL);
		/*Set Parity bits*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8ParityBits;
		/*Set Stop bit*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8PStopBit;
		/*Check 9 bit*/
		if(Add_pstrConfigue->UART_u8DataBits == UART_u8_NINE_DATA_BITS)
		{
			UART_UCSRC |= 0x04;
		}
		/*Set Character Size*/
		UART_UCSRC |= Add_pstrConfigue->UART_u8DataBits;
		/*Choose Transmit or Receive*/
		UART_UCSRB |= Add_pstrConfigue->UART_u8Mode;

		/*enable RXCIE RX complete interrupt*/
		Set_Bit(UART_UCSRB,UART_RXCIE);

		/*Enable UBRRH -> URSEL = 0*/
		clear_Bit(UART_UCSRC, UART_URSEL);
		/*Set Baud Rate*/
		UART_UBRRL |= (u8)(Add_pstrConfigue->UART_u16BaudRate);
		UART_UBRRH |= (u8)((Add_pstrConfigue->UART_u16BaudRate) >> 8);
	}
	return Local_enuErrorStatus;
}
UART_tenuErrorStatus UART_enuTransmite (u16 Copy_pu16Data)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;
	if(0)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
		/*Polling on the flag -> wait for UDR to be empty*/
		while((Get_Bit(UART_UCSRA, UART_UDRE)) == 0);

		/*Clear TXB8*/
		clear_Bit(UART_UCSRB, UART_TXB8);
		if ( Copy_pu16Data & 0x0100 )
		{
			Set_Bit(UART_UCSRB, UART_TXB8);
		}
		/* Put data into UDR Register */
		UART_UDR = (u8)(Copy_pu16Data);
	}
	return Local_enuErrorStatus;
}

UART_tenuErrorStatus UART_enuReceive (u8* Add_pu8Data)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;
	if(Add_pu8Data == NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
		/*Polling on the flag -> wait for data to be received*/
		while((Get_Bit(UART_UCSRA,UART_RXC)) == 0);
		/*Check frame error and Data over Run error*/
		if((Get_Bit(UART_UCSRA,UART_DOR)) || (Get_Bit(UART_UCSRA,UART_FE)))
		{
			Local_enuErrorStatus= UART_NOK;
		}
		else
		{
			//*Add_pu16Data =(((UART_u8_UCSRB_REG>>1) & 0X01) << 8); // get bit number 9
			*Add_pu8Data |= UART_UDR;     // get Lowbyte
		}
	}
	return Local_enuErrorStatus;
}
void UART_InterruptReceive(u8* Add_pu8Data)
{
	*Add_pu8Data |= UART_UDR;     // get Lowbyte
}
void UART_CallBackFunctionRX(void (*PTF)(void))
{
	GPTF_RX = PTF;
}
void __vector_13(void)
{
	GPTF_RX();
}
