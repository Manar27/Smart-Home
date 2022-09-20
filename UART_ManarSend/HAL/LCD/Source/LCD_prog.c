/*
 * LCD_prog.c
 *
 *  Created on: Aug 11, 2022
 *      Author: Manar
 */
#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"
#include "../Header/LCD_Private.h"
#include "../Header/LCD_interface.h"
#include "../Header/LCD_Config.h"

#include <stdio.h>
#include <util/delay.h>

void LCD_VoidSendCommand(u8 Local_command)
{
	/*set RS pin to command --> 0*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_RS_Pin,Low);
	/*set RW pin to write --> 0*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_RW_Pin,Low);
	/*set Enable pin to High*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_E_Pin,High);
	/*send the command line*/
	DIO_VoidSetPortValue(LCD_DataGroup,Local_command);
	/*set Enable pin to Low*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_E_Pin,Low);
}
void LCD_VoidSendChar(u8 Local_char)
{
	/*set RS pin to Data --> 1*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_RS_Pin,High);
	/*set RW pin to write --> 0*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_RW_Pin,Low);
	/*set Enable pin to Low*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_E_Pin,High);
	/*send the char*/
	DIO_VoidSetPortValue(LCD_DataGroup,Local_char);
	/*set Enable pin to Low*/
	DIO_VoidSetPinValue(LCD_Control_Group,LCD_E_Pin,Low);
}
void LCD_Void8BitInit(void)
{
	/*Select The Directions*/
	DIO_VoidSetPortDir(LCD_DataGroup,Max_Output);
	DIO_VoidSetPinDir(LCD_Control_Group, LCD_RS_Pin, Output);
	DIO_VoidSetPinDir(LCD_Control_Group, LCD_RW_Pin, Output);
	DIO_VoidSetPinDir(LCD_Control_Group, LCD_E_Pin, Output);

	/*wait for more than 30ms after power up*/
	_delay_ms(35);
	/*function set*/
	LCD_VoidSendCommand(LCD_Set8Bit2Line5x8);
	/*wait for more than 39us*/
	_delay_ms(1);
	/*Display On off control*/
	LCD_VoidSendCommand(LCD_CursorON);
	/*wait for more than 39us*/
	_delay_ms(1);
	/*Clear LCD*/
	LCD_VoidSendCommand(LCD_ClearDisplay);
	/*wait for more than 1.53ms*/
	_delay_ms(2);
	/*Entry Mode*/
	LCD_VoidSendCommand(LCD_EntryMode2);
	_delay_ms(1);
}
void LCD_VoidSendString (char *Ref_string)
{
	while (*Ref_string != '\0')
	{
		LCD_VoidSendChar(*Ref_string);
		Ref_string++;
	}
}
void LCD_VoidSendNumber(u32 Local_Number)
{
	u32 Local_ReversedNum = 2;
	while (Local_Number != 0)
	{
		Local_ReversedNum = (Local_ReversedNum*10) + (Local_Number % 10);
		Local_Number = Local_Number / 10;
	}
	do
	{
		LCD_VoidSendChar((Local_ReversedNum%10)+ '0');
		Local_ReversedNum /= 10;
	}while(Local_ReversedNum != 2);
	/*u32 Reminder = 0;
	u16 arr[sizeof(u32)] = {0};
	u32 i = 0;
	while(Local_Number != 0)
	{
		Reminder = Local_Number % 10 ;
		Local_Number /= 10;
		arr[i] = Reminder;
		i++;
	}
	for (int count = i-1; count >= 0; count--)
	{
		LCD_VoidSendChar(arr[count] + '0');
	}*/
}
void LCD_VoidStartFrom(u8 Local_RowPosition, u8 Local_ColPosition)
{
	if((Local_ColPosition < Cols_Number) && (Local_RowPosition < Rows_Number))
	{
		u8 Local_DDRAMAddress = LCD_SetAddressDDRAM + (Local_RowPosition * Line1_Address) + Local_ColPosition;
		LCD_VoidSendCommand(Local_DDRAMAddress);
	}
}
void LCD_VoidSendStringFromPos (char *Ref_string, u8 Local_RowPosition, u8 Local_ColPosition)
{
	u8 Local_Index = 0;
	u8 line;
	if (Local_RowPosition == 0)
	{
		line = Line_1;
	}
	else if (Local_RowPosition == 1)
	{
		line = Line_2;
	}
	LCD_VoidStartFrom(Local_RowPosition,Local_ColPosition);
	while ((Ref_string[Local_Index] != '\0') && (((Local_RowPosition * Cols_Number) + (Local_ColPosition + Local_Index)) < Total_blocks_Num))
	{
		if((Local_RowPosition*16) + (Local_ColPosition + Local_Index) < Cols_Number)
		{
			LCD_VoidSendChar(Ref_string[Local_Index]);
			Local_Index++;
		}
		else if(((Local_RowPosition*16) + (Local_ColPosition + Local_Index) == Cols_Number) && (line == Line_1))
		{
			LCD_VoidStartFrom(1,0);
			line = Line_2;
			Local_RowPosition = 1;
			Local_ColPosition = 0;
		}
		else if(((Local_RowPosition*16) + (Local_ColPosition + Local_Index) < Total_blocks_Num) && (line == Line_2))
		{
			LCD_VoidSendChar(Ref_string[Local_Index]);
			Local_Index++;
			if(((Local_RowPosition*16) + (Local_ColPosition + Local_Index)) == Total_blocks_Num)
			{
				LCD_VoidStartFrom(0,0);
				Local_RowPosition = 0;
				Local_ColPosition = 0;
				line = Line_1;
			}
		}
	}
}
void LCD_VoidAddCustomPattern(u8 * Local_Pattern, u8 Local_IndexCGRAM)
{
	if(Local_IndexCGRAM < CGRAM_MaxSize)
	{
		u8 Local_CGRAMAddress = LCD_SetAddressCGRAM + Local_IndexCGRAM * CGRAM_MaxSize;
		LCD_VoidSendCommand(Local_CGRAMAddress);
		for(int index = 0; index < CGRAM_MaxSize; index++)
		{
			LCD_VoidSendChar(Local_Pattern[index]);
		}
		LCD_VoidSendCommand(LCD_ReturnHome);
		/*Wait more than 1.53ms after ReturnHome Command*/
		_delay_ms(2);
	}
}
void LCD_VoidCustomDisplay(u8 Local_CGRAMIndex, u8 Local_RowPosition, u8 Local_ColPosition)
{
	LCD_VoidStartFrom(Local_RowPosition, Local_ColPosition);
	LCD_VoidSendChar(Local_CGRAMIndex);
}
void LCD_VoidRightShift (char *Ref_string)
{
	u8 Local_RowPosition = 0;
	u8 Local_ColPosition = 0;
	while(1){
		while(Local_RowPosition == Line_1)
		{
			LCD_VoidSendStringFromPos(Ref_string,0,0);
			LCD_VoidSendCommand(LCD_DisplayShift);
			_delay_ms(DisplayShiftDelay);
			Local_ColPosition++;
			if (Local_ColPosition == Cols_Number)
			{
				Local_ColPosition = 0;
				Local_RowPosition = Line_2;
			}
		}
		LCD_VoidSendCommand(LCD_ClearDisplay);
		_delay_ms(2);
		while(Local_RowPosition == Line_2)
		{
			LCD_VoidSendStringFromPos(Ref_string,1,0);
			LCD_VoidSendCommand(LCD_DisplayShift);
			_delay_ms(DisplayShiftDelay);
			Local_ColPosition++;
			if (Local_ColPosition == Cols_Number)
			{
				Local_ColPosition = 0;
				Local_RowPosition = Line_1;
			}
		}
	}
}
