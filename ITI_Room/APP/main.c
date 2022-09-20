/*
 * main.c
 *
 *  Created on: Sep 12, 2022
 *      Author: Manar
 */
#include "../Common/Bit_math.h"
#include "../Common/Macro's.h"
#include "../Common/typedef.h"
#include "../HAL/LCD/Header/LCD_interface.h"
#include "../HAL/LDR/Header/LDR_interface.h"
#include "../HAL/LED/Header/LED_interface.h"
#include "../HAL/DCM/Header/DCM_Interface.h"
#include "../HAL/TEMP/Header/TEMPL35_Interface.h"

#include "../MCAL/DIO/Header/DIO_interface.h"
#include "../MCAL/ADC/Header/ADC_interface.h"
#include "../MCAL/Timer0/Header/Timer0_Interface.h"
#include "../MCAL/GIE/Header/GIE_interface.h"
#include "../MCAL/UART/Header/UART_Interface.h"

#define LDR_Resistor 10000

void TimerFun (void);
void UART_Interrupt_Fun (void);

u8 UART_RecValue = 0;
u8 UART_LightsFlag = 0;
u8 UART_FanFlag = 0;

volatile u8 seconds = 0;

#include <util/delay.h>
void main (void)
{
	LCD_Void8BitInit();
	LED_VoidInit();
	Timer0_CallBackFunctionNormal(TimerFun);
	UART_CallBackFunctionRX(UART_Interrupt_Fun);

	UART_tstrConfiguration object ;
	object.UART_u8Mode = UART_u8_Recieve;
	object.UART_u16BaudRate = UART_u16_BAUD_RATE_9600;
	object.UART_u8DataBits = UART_u8_EIGHT_DATA_BITS;
	object.UART_u8PStopBit = UART_u8_ONE_STOP_BIT;
	object.UART_u8ParityBits = UART_u8_DISABLED_PARITY;

	GIE_VoidEnable();
	UART_enuInitRXInterrupt(&object);

	u8 minuts = 29;
	u8 hours = 2;
	u8 Temperature;
	u32 LDR_Value;

	ADC_VoidInitPolling();

	Timer0_VoidInitNormal(123);
	GIE_VoidEnable();

	while (1)
	{
		/*Clock*/
		if (seconds == 60)
		{
			LCD_VoidSendCommand(LCD_ClearDisplay);
			_delay_ms(2);
			seconds = 0;
			minuts++;
			if (minuts == 60)
			{
				LCD_VoidSendCommand(LCD_ClearDisplay);
				_delay_ms(2);
				minuts = 0;
				hours++;
				if (hours == 24)
				{
					hours = 0;
				}
			}
		}
		/*Display Clock*/
		LCD_VoidStartFrom(0,0);
		_delay_ms(200);
		LCD_VoidSendString("Time:  ");
		_delay_ms(200);
		LCD_VoidSendNumber(hours);
		_delay_ms(200);
		LCD_VoidSendString(":");
		_delay_ms(200);
		LCD_VoidSendNumber(minuts);
		_delay_ms(200);
		LCD_VoidSendString(":");
		_delay_ms(200);
		LCD_VoidSendNumber(seconds);

		/*Get Temperature*/
		Temperature = TEMPL35_u8GetTemp(1);

		/*Display temperature*/
		LCD_VoidStartFrom(1,0);
		LCD_VoidSendString("Temp:  ");
		LCD_VoidSendNumber(Temperature);
		LCD_VoidSendString(" C     ");

		/*Temperature Action*/
		if(Temperature >= 50)
		{
			/*ALARM On*/
			DIO_VoidSetPinValue(Group_B,Pin_B0,High);
		}
		else if(UART_FanFlag == 1)
		{
			DCM_VoidInitSingleControl(DCM_Start);
		}
		else if (UART_FanFlag == 0)
		{
			if ((Temperature > 30 && Temperature < 50))
			{
				/*FAN on, ALARM off*/
				DIO_VoidSetPinValue(Group_B,Pin_B0,Low);
				DCM_VoidInitSingleControl(DCM_Start);
			}
			else if (Temperature < 30)
			{
				/*Both off*/
				DIO_VoidSetPinValue(Group_B,Pin_B0,Low);
				DCM_VoidInitSingleControl(DCM_Stop);
			}
			else
			{
				//Alarm is ON -> fan off
				DCM_VoidInitSingleControl(DCM_Stop);
			}
		}
		/*Get LDR*/
		LDR_Value = LDR_u8GetValue(0,LDR_Resistor);

		/*LDR action*/
		if(UART_LightsFlag == 1)
		{
			/*Lights on*/
			LED_VoidTurnOnAll();
		}
		else if(UART_LightsFlag == 0)
		{
			if (LDR_Value < 400)
			{
				/*Lights off*/
				LED_VoidTurnOffAll();
			}
			else if (LDR_Value >= 400)
			{
				/*Lights on*/
				LED_VoidTurnOnAll();
			}
		}
	}
}
void TimerFun (void)
{
	static u8 TimerCounter = 0;
	TimerCounter++;
	/*1 Second*/
	if (TimerCounter == 31)
	{
		seconds++;
		TimerCounter = 0;
		Timer0_VoidSetPreload(123);
	}
}
void UART_Interrupt_Fun (void)
{
	UART_InterruptReceive(&UART_RecValue);
	if (UART_RecValue == 'L')
	{
		UART_LightsFlag = 1;
	}
	else if (UART_RecValue == 'O')
	{
		UART_LightsFlag = 0;
	}
	else if (UART_RecValue == 'F')
	{
		UART_FanFlag = 1;
	}
	else if (UART_RecValue == 'T')
	{
		UART_FanFlag = 0;
	}
	UART_RecValue = 0;
}
