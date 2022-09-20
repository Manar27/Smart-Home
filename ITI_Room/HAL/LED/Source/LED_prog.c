/*
 * LED_prog.c
 *
 *  Created on: Aug 14, 2022
 *      Author: Manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"
#include "../Header/LED_Config.h"
#include "../Header/LED_interface.h"

void LED_VoidInit(void)
{
	for(int i = 0; i < LEDs_Num; i++)
	{
		DIO_VoidSetPinDir(LEDs_Group, LED1 + i,Output);
	}
}

void LED_VoidTurnOffAll(void)
{
	for(int i = 0; i < LEDs_Num; i++)
	{
		DIO_VoidSetPinValue(LEDs_Group, LED1 + i,Low);
	}
}

void LED_VoidTurnOnAll(void)
{
	for(int i = 0; i < LEDs_Num; i++)
	{
		DIO_VoidSetPinValue(LEDs_Group, LED1 + i,High);
	}
}
void LED_VoidToggleAll(void)
{
	for(int i = 0; i < LEDs_Num; i++)
	{
		DIO_VoidToggleBit(LEDs_Group, LED1 + i);
	}
}
void LED_VoidTurnOnOne(u8 Local_LED_number)
{
	DIO_VoidSetPinDir(LEDs_Group,Local_LED_number,Output);
	DIO_VoidSetPinValue(LEDs_Group, Local_LED_number, High);
}

void LED_VoidTurnOffOne(u8 Local_LED_number)
{
	DIO_VoidSetPinValue(LEDs_Group, Local_LED_number, Low);
}
void LED_VoidToggleOne(u8 Local_LED_number)
{
	DIO_VoidToggleBit(LEDs_Group,Local_LED_number);
}
void LED_VoidTurnOnRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count < Local_LED_number+Local_NumberOfLEDs; Local_Count++)
	{
		DIO_VoidSetPinValue(LEDs_Group, Local_Count, High);
	}
}
void LED_VoidTurnOnLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count > Local_LED_number-Local_NumberOfLEDs; Local_Count--)
	{
		DIO_VoidSetPinValue(LEDs_Group, Local_Count, High);
	}
}
void LED_VoidTurnOffRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count < Local_LED_number+Local_NumberOfLEDs; Local_Count++)
	{
		DIO_VoidSetPinValue(LEDs_Group, Local_Count, Low);
	}
}
void LED_VoidTurnOffLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count > Local_LED_number-Local_NumberOfLEDs; Local_Count--)
	{
		DIO_VoidSetPinValue(LEDs_Group, Local_Count, Low);
	}
}
void LED_VoidToggleRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count < Local_LED_number+Local_NumberOfLEDs; Local_Count++)
	{
		DIO_VoidToggleBit(LEDs_Group, Local_Count);
	}
}
void LED_VoidToggleLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs)
{
	u8 Local_Count = 0;
	for (Local_Count = Local_LED_number; Local_Count > Local_LED_number-Local_NumberOfLEDs; Local_Count--)
	{
		DIO_VoidToggleBit(LEDs_Group, Local_Count);
	}
}
