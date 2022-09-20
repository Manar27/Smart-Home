/*
 * UART_prg.c
 *
 *  Created on: Sep 9, 2022
 *      Author: Dell
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/UART_int.h"
#include "../Header/UART_prv.h"
static void (*GPTF_RX) (void) = NULL;

UART_tenuErrorStatus  UART_enuInit(UART_tstrConfiguration* Add_pstrConfigue)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;

	if(Add_pstrConfigue== NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
        UART_u8_UCSRC_REG |=(1<<7);   //URSEL Set to 1
		// Set Parity bits
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8ParityBits;

         // Set Stop bit
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8PStopBit;

         //check 9 bit
         if(Add_pstrConfigue->UART_u8DataBits == UART_u8_NINE_DATA_BITS)
         {
        	 UART_u8_UCSRB_REG |=0x04;
         }

         // Set Character Size
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8DataBits;

         //Choose Transmite or Receive
         UART_u8_UCSRB_REG |=Add_pstrConfigue->UART_u8Mode;

         // set Baud Rate
         UART_u8_UCSRC_REG &=~(1<<7);   //URSEL Set to 0
         UART_u8_UBRRL_REG |= (u8)(Add_pstrConfigue->UART_u16BaudRate);
         UART_u8_UBRRH_REG |= (u8)((Add_pstrConfigue->UART_u16BaudRate)>>8);

	}

	return Local_enuErrorStatus;
}
UART_tenuErrorStatus  UART_enuInitRXInterrupt(UART_tstrConfiguration* Add_pstrConfigue)
{

	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;

	if(Add_pstrConfigue== NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{
        UART_u8_UCSRC_REG |=(1<<7);   //URSEL Set to 1
		// Set Parity bits
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8ParityBits;

         // Set Stop bit
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8PStopBit;

         //check 9 bit
         if(Add_pstrConfigue->UART_u8DataBits == UART_u8_NINE_DATA_BITS)
         {
        	 UART_u8_UCSRB_REG |=0x04;
         }

         // Set Character Size
         UART_u8_UCSRC_REG |=Add_pstrConfigue->UART_u8DataBits;

         //Choose Transmite or Receive
         UART_u8_UCSRB_REG |=Add_pstrConfigue->UART_u8Mode;
         /*enable RXICE Rx complete interrupt*/
         UART_u8_UCSRB_REG |= (1<<7);

         // set Baud Rate
         UART_u8_UCSRC_REG &=~(1<<7);   //URSEL Set to 0
         UART_u8_UBRRL_REG |= (u8)(Add_pstrConfigue->UART_u16BaudRate);
         UART_u8_UBRRH_REG |= (u8)((Add_pstrConfigue->UART_u16BaudRate)>>8);


	}

	return Local_enuErrorStatus;
}
UART_tenuErrorStatus  UART_enuTransmite(u16 Copy_pu16Data)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;

	if(0)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{

	       // poling on the flag >>> wait for UDR to be empty
     while(((UART_u8_UCSRA_REG >> 5) & 0x01 )== 0);

     UART_u8_UCSRB_REG &= ~(1<<0);  // Clear TXB8
     if ( Copy_pu16Data & 0x0100 )
     {
    	 UART_u8_UCSRB_REG |= 0x01; //Set TXB8
     }
     /* Put data into UDR Register */
     UART_u8_UDR_REG = (u8)(Copy_pu16Data);


	}

	return Local_enuErrorStatus;
}

UART_tenuErrorStatus  UART_enuReceive(u8* Add_pu16Data)
{
	UART_tenuErrorStatus Local_enuErrorStatus= UART_OK;

	if(Add_pu16Data==NULL)
	{
		Local_enuErrorStatus= UART_NOK;
	}
	else
	{

	       // poling on the flag >>> wait for data to be received
	     while(((UART_u8_UCSRA_REG >> 7) & 0x01 )== 0);

	      // check frame error and Data over Run error
	     if(((UART_u8_UCSRA_REG>>3) & 0x01) || ((UART_u8_UCSRA_REG>>4) & 0x01))
	     {
	    	 Local_enuErrorStatus= UART_NOK;
	     }
	     else
	     {
	    	// *Add_pu16Data =(((UART_u8_UCSRB_REG>>1) & 0X01) << 8); // get bit number 9
	    	*Add_pu16Data = UART_u8_UDR_REG;     // get Lowbyte
	     }
	}

	return Local_enuErrorStatus;
}
void UART_CallBackFunctionRX(void (*PTF)(void))
{
	GPTF_RX = PTF;
}
void __vector_13(void)
{
	GPTF_RX();
}
