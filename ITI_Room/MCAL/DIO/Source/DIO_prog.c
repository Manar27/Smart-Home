/*
 * DIO_program.c
 *
 *  Created on: Aug 8, 2022
 *      Author: Manar
 */

#include "../../../Common/typedef.h"
#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../Header/DIO_interface.h"
#include "../Header/DIO_Private.h"
#include "../Header/DIO_Register.h"

void DIO_VoidSetPinDir(u8 Local_Groupname, u8 Local_PinNumber, u8 Local_DirectionState)
{
	if (Local_Groupname <= Group_D && Local_PinNumber <= Pin_D7)
	{
		if (Local_DirectionState == Input)
		{
			switch (Local_Groupname)
			{
				case Group_A :
					clear_Bit(DIO_DDRA, Local_PinNumber);
					break;
				case Group_B :
					clear_Bit (DIO_DDRB, Local_PinNumber);
					break;
				case Group_C :
					clear_Bit (DIO_DDRC, Local_PinNumber);
					break;
				case Group_D :
					clear_Bit (DIO_DDRD, Local_PinNumber);
					break;
			}
		}
		else if (Local_DirectionState == Output)
		{
			switch (Local_Groupname)
			{
				case Group_A :
					Set_Bit(DIO_DDRA, Local_PinNumber);
					break;
				case Group_B :
					Set_Bit(DIO_DDRB, Local_PinNumber);
					break;
				case Group_C :
					Set_Bit(DIO_DDRC, Local_PinNumber);
					break;
				case Group_D :
					Set_Bit(DIO_DDRD, Local_PinNumber);
					break;
			}
		}
	}
}
void DIO_VoidSetPinValue(u8 Local_Groupname, u8 Local_PinNumber, u8 Local_valueState)
{
	if (Local_Groupname <= Group_D && Local_PinNumber <= Pin_D7)
	{
		if (Local_valueState == Low)
		{
			switch (Local_Groupname)
			{
				case Group_A:
					clear_Bit(DIO_PORTA, Local_PinNumber);
					break;
				case Group_B:
					clear_Bit(DIO_PORTB, Local_PinNumber);
					break;
				case Group_C:
					clear_Bit(DIO_PORTC, Local_PinNumber);
					break;
				case Group_D:
					clear_Bit(DIO_PORTD, Local_PinNumber);
					break;
			}
		}
		else if (Local_valueState == High)
		{
			switch (Local_Groupname)
			{
				case Group_A:
					Set_Bit(DIO_PORTA, Local_PinNumber);
					break;
				case Group_B:
					Set_Bit(DIO_PORTB, Local_PinNumber);
					break;
				case Group_C:
					Set_Bit(DIO_PORTC, Local_PinNumber);
					break;
				case Group_D:
					Set_Bit(DIO_PORTD, Local_PinNumber);
					break;
			}
		}
	}
}
u8	 DIO_u8GetPinValue (u8 Local_Groupname, u8 Local_PinNumber)
{
	u8 Local_returndata = 0;
	if (Local_Groupname <= Group_D && Local_PinNumber <= Pin_D7)
	{
		switch (Local_Groupname)
		{
			case Group_A:
				Local_returndata = Get_Bit(DIO_PINA, Local_PinNumber);
				break;
			case Group_B:
				Local_returndata = Get_Bit(DIO_PINB, Local_PinNumber);
				break;
			case Group_C:
				Local_returndata = Get_Bit(DIO_PINC, Local_PinNumber);
				break;
			case Group_D:
				Local_returndata = Get_Bit(DIO_PIND, Local_PinNumber);
				break;
		}
		return Local_returndata;
	}
	else
	{
		return -1;
	}
}
void DIO_VoidSetPortDir(u8 Local_Groupname, u8 Local_DirectionState)
{
	switch (Local_Groupname)
	{
		case Group_A:
			DIO_DDRA = Local_DirectionState;
			break;
		case Group_B:
			DIO_DDRB = Local_DirectionState;
			break;
		case Group_C:
			DIO_DDRC = Local_DirectionState;
			break;
		case Group_D:
			DIO_DDRD = Local_DirectionState;
			break;
	}
}
void DIO_VoidSetPortValue(u8 Local_Groupname, u8 Local_valueState)
{
	switch (Local_Groupname)
	{
		case Group_A:
			DIO_PORTA = Local_valueState;
			break;
		case Group_B:
			DIO_PORTB = Local_valueState;
			break;
		case Group_C:
			DIO_PORTC = Local_valueState;
			break;
		case Group_D:
			DIO_PORTD = Local_valueState;
			break;
	}
}
u8	 DIO_u8GetPortValue (u8 Local_Groupname)
{
	u8 Local_returndata = 0;
	if (Local_Groupname <= Group_D)
	{
		switch (Local_Groupname)
		{
			case Group_A:
				Local_returndata = DIO_PINA;
				break;
			case Group_B:
				Local_returndata = DIO_PINB;
				break;
			case Group_C:
				Local_returndata = DIO_PINC;
				break;
			case Group_D:
				Local_returndata = DIO_PIND;
				break;
		}
		return Local_returndata;
	}
	else
	{
		return -1;
	}
}
void DIO_VoidToggleBit(u8 Local_Groupname, u8 Local_PinNumber)
{
	switch (Local_Groupname)
	{
		case Group_A:
			toggle_Bit(DIO_PORTA, Local_PinNumber);
			break;
		case Group_B:
			toggle_Bit(DIO_PORTB, Local_PinNumber);
			break;
		case Group_C:
			toggle_Bit(DIO_PORTC, Local_PinNumber);
			break;
		case Group_D:
			toggle_Bit(DIO_PORTD, Local_PinNumber);
			break;
	}
}
void DIO_VoidTogglePORT(u8 Local_Groupname)
{

	switch (Local_Groupname)
	{
		case Group_A:
			DIO_PORTA = ~DIO_PORTA;
			break;
		case Group_B:
			DIO_PORTB = ~DIO_PORTB;
			break;
		case Group_C:
			DIO_PORTC = ~DIO_PORTC;
			break;
		case Group_D:
			DIO_PORTD = ~DIO_PORTD;
			break;
	}

}

