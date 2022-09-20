#include "../Common/Bit_math.h"
#include "../Common/Macro's.h"
#include "../Common/typedef.h"

#include "../MCAL/DIO/Header/DIO_interface.h"
#include "../MCAL/UART/Header/UART_int.h"
#include "../HAL/LCD/Header/LCD_interface.h"
#include "../HAL/KPD/Header/KPD_Interface.h"

#include <util/delay.h>
void main (void)
{
	LCD_Void8BitInit();

	u8 Key_Value;
	DIO_VoidSetPinDir(Group_B,Pin_B0,Output);
	DIO_VoidSetPinValue(Group_B,Pin_B0,Low);

	DIO_VoidSetPinDir(Group_D,Pin_D1,Output);
	DIO_VoidSetPinValue(Group_D,Pin_D1,Low);

	DIO_VoidSetPinDir(Group_D, Pin_D0, Input);
	DIO_VoidSetPinValue(Group_D,Pin_D0,High);


	UART_tstrConfiguration object;
	object.UART_u16BaudRate = UART_u16_BAUD_RATE_9600;
	object.UART_u8DataBits = UART_u8_EIGHT_DATA_BITS;
	object.UART_u8Mode = UART_u8_Transmite;
	object.UART_u8PStopBit = UART_u8_ONE_STOP_BIT;
	object.UART_u8ParityBits = UART_u8_DISABLED_PARITY;

	while(1)
	{
		Key_Value = Keypad_GetPressedKey();
		_delay_ms(250);

		UART_enuInit(&object);
		UART_tenuErrorStatus error_status = UART_enuTransmite(Key_Value);
		if (error_status == UART_OK)
		{
			DIO_VoidSetPinValue(Group_B, Pin_B0, High);
			_delay_ms(1000);
			DIO_VoidSetPinValue(Group_B, Pin_B0, Low);
		}
		else
		{
			DIO_VoidSetPinValue(Group_B, Pin_B0, Low);
		}
		LCD_VoidSendCommand(LCD_ClearDisplay);
		_delay_ms(2);
		LCD_VoidSendChar(Key_Value);
		_delay_ms(500);
	}
}
