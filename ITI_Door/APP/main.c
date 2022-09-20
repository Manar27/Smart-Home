/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Manar
 */
#include "../Common/Bit_math.h"
#include "../Common/Macro's.h"
#include "../Common/typedef.h"

#include "../HAL/KPD/Header/KPD_Interface.h"
#include "../HAL/LCD/Header/LCD_interface.h"

#include "../MCAL/DIO/Header/DIO_interface.h"
#include "../MCAL/DIO/Header/DIO_Register.h"
#include "../MCAL/UART/Header/UART_Interface.h"
#include "../MCAL/GIE/Header/GIE_interface.h"

void UART_Interrupt_Fun (void);
u8 UART_RecValue = 0;

#include <util/delay.h>
void main (void)
{
	UART_CallBackFunctionRX(UART_Interrupt_Fun);

	UART_tstrConfiguration object ;
	object.UART_u8Mode = UART_u8_Recieve;
	object.UART_u16BaudRate = UART_u16_BAUD_RATE_9600;
	object.UART_u8DataBits = UART_u8_EIGHT_DATA_BITS;
	object.UART_u8PStopBit = UART_u8_ONE_STOP_BIT;
	object.UART_u8ParityBits = UART_u8_DISABLED_PARITY;

	GIE_VoidEnable();
	//UART_enuInit(&object);
	UART_enuInitRXInterrupt(&object);

	//u8 UART_Flag = 0;

	u8 Key_Value;
	u8 Chosen_Mode = 0;
	u32 Saved_Pass = 1234;
	u32 Reversed_Pass = 4321;
	u32 Get_Reversed_Pass = 0;
	u32 Temp_Pass = 0;
	u32 Comp_Pass = 0;
	u8 motor_steps[2] = {6,3};
	DIO_VoidSetPortDir(Group_C,0x0f);
	DIO_VoidSetPortValue(Group_C,0xf0);
	DIO_VoidSetPinDir(Group_D,Pin_D4,Output);

	LCD_Void8BitInit();
	LCD_VoidSendStringFromPos("Welcome Home",0,2);
	_delay_ms(250);

	while(1)
	{
		LCD_VoidSendCommand(LCD_ClearDisplay);
		_delay_ms(2);
		LCD_VoidSendStringFromPos("Choose a Mode",0,2);
		_delay_ms(500);
		LCD_VoidSendCommand(LCD_ClearDisplay);
		_delay_ms(2);
		LCD_VoidSendString("1- Enter Pass");
		LCD_VoidSendStringFromPos("2- Change Pass",1,0);
		Chosen_Mode = Keypad_GetPressedKey();
		DIO_VoidSetPinValue(Group_D,Pin_D4,Low);

		/*Code to get the Password From the User*/
		if (Chosen_Mode == 1)
		{
			LCD_VoidSendCommand(LCD_ClearDisplay);
			_delay_ms(2);
			LCD_VoidSendString("Password : ");
			for (u8 i = 0; i < 4 ; i++)
			{
				LCD_VoidSendCommand(LCD_CursorON);
				_delay_ms(100);
				LCD_VoidSendCommand(LCD_CURSOROFF);

				Key_Value = Keypad_GetPressedKey();
				if ((Key_Value >= 0) && (Key_Value <= 9))
				{
					LCD_VoidSendNumber(Key_Value);
					_delay_ms(200);
					LCD_VoidSendStringFromPos("*",0,11+i);
				}
				else
				{
					LCD_VoidSendCommand(LCD_ClearDisplay);
					_delay_ms(2);
					LCD_VoidSendStringFromPos("Invalid Input",0,1);
					_delay_ms(500);
					break;
				}
				Comp_Pass += Key_Value;
				Comp_Pass = Comp_Pass * 10;
			}
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(500);

			if (Saved_Pass == Comp_Pass)
			{
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				LCD_VoidSendString("Welcome Back");

				DIO_PORTC = (DIO_PORTC & 0xF0) | (motor_steps[1] & 0x0F);  // 90
				_delay_ms(1000);
				DIO_PORTC = (DIO_PORTC & 0xF0) | (motor_steps[0] & 0x0F);  //   0

				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				Comp_Pass = 0;
			}
			else if (Reversed_Pass == Comp_Pass)
			{
				LCD_VoidSendStringFromPos("Calling 911",0,1);
				_delay_ms(1000);
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				Comp_Pass = 0;
			}
			else
			{
				LCD_VoidSendStringFromPos("Wrong Password",0,1);
				_delay_ms(500);
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				Comp_Pass = 0;
			}
		}

		// Code to Change the Password
		else if (Chosen_Mode == 2)
		{
			LCD_VoidSendCommand(LCD_ClearDisplay);
			_delay_ms(2);
			LCD_VoidSendString("Old Pass : ");
			for (u8 i = 0; i<4 ;i++)
			{
				LCD_VoidSendCommand(LCD_CursorON);
				_delay_ms(200);
				LCD_VoidSendCommand(LCD_CURSOROFF);

				Key_Value = Keypad_GetPressedKey();
				if ((Key_Value >= 0) && (Key_Value <= 9))
				{
					LCD_VoidSendNumber(Key_Value);
					_delay_ms(200);
					LCD_VoidSendStringFromPos("*",0,11+i);
				}
				else
				{
					LCD_VoidSendCommand(LCD_ClearDisplay);
					_delay_ms(2);
					LCD_VoidSendStringFromPos("Invalid Input",0,1);
					_delay_ms(500);
					break;
				}
				/*10+2 120+3 1230+4 12340*/
				Comp_Pass += Key_Value;
				Comp_Pass = Comp_Pass * 10;
			}
			/*12340->1234*/
			Comp_Pass = Comp_Pass / 10;
			_delay_ms(500);
			LCD_VoidSendCommand(LCD_ClearDisplay);
			_delay_ms(2);
			if (Saved_Pass == Comp_Pass)
			{
				Comp_Pass = 0;
				Saved_Pass = 0;
				Reversed_Pass = 0;
				Get_Reversed_Pass = 0;
				LCD_VoidSendString("New Pass : ");
				LCD_VoidSendStringFromPos("Just Numbers",1,0);
				for (u8 i = 0; i<4 ;i++)
				{
					LCD_VoidSendCommand(LCD_CursorON);
					_delay_ms(200);
					LCD_VoidSendCommand(LCD_CURSOROFF);

					Key_Value = Keypad_GetPressedKey();
					if ((Key_Value >= 0) && (Key_Value <= 9))
					{
						LCD_VoidStartFrom(0,11+i);
						LCD_VoidSendNumber(Key_Value);
						/*Integer_TO_String (key);*/
						_delay_ms(200);
						LCD_VoidSendStringFromPos("*",0,11+i);
					}

					Saved_Pass += Key_Value;
					Saved_Pass = Saved_Pass * 10;
				}
				Saved_Pass = Saved_Pass / 10;
				Temp_Pass = Saved_Pass;
				while (Temp_Pass > 0)
				{
					Get_Reversed_Pass = Temp_Pass % 10;
					Reversed_Pass = (Reversed_Pass * 10) + Get_Reversed_Pass;
					Temp_Pass = Temp_Pass / 10;
				}
				_delay_ms(500);
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				LCD_VoidSendString("Password changed");
				_delay_ms(500);
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
			}
			else
			{
				LCD_VoidSendStringFromPos("Wrong Password",0,1);
				_delay_ms(500);
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				Comp_Pass = 0;
			}
		}
		else
		{
			LCD_VoidSendCommand(LCD_ClearDisplay);
			_delay_ms(2);
			LCD_VoidSendStringFromPos("Invalid Input",0,1);
			_delay_ms(500);
		}
	}
}
void UART_Interrupt_Fun (void)
{
	UART_InterruptReceive(&UART_RecValue);
	if (UART_RecValue == 'A')
	{
		LCD_VoidSendCommand(LCD_ClearDisplay);
		_delay_ms(2);
		LCD_VoidSendString("Welcome Back");
		DIO_PORTC = (DIO_PORTC & 0xF0) | (3 & 0x0F);  // 90
		_delay_ms(1000);
		DIO_PORTC = (DIO_PORTC & 0xF0) | (6 & 0x0F);  //   0
	}
	UART_RecValue = 0;
}
