/*
 * KPD_Prog.c
 *
 *  Created on: Aug 22, 2022
 *      Author: Manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/KPD_Config.h"
#include "../Header/KPD_Interface.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"
#include "../../../MCAL/DIO/Header/DIO_Register.h"

/***************************************************************************************************/
/****************************************Function Prototypes****************************************/


#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number);


#elif (N_COL == 4)

static u8 Keypad_4x4_adjustKeyNumber (u8 button_number);

#endif

/**************************************************************************************************/
/****************************************Function Definition***************************************/

u8 Keypad_GetPressedKey(void)
{
	u8 Local_Row, Local_Col;
	while(1)
	{
		for (Local_Col = 0; Local_Col < N_COL; Local_Col++)
		{
			//DIO_VoidSetPortDir(KEYPAD_PORT,(0b00010000 << Local_Col));
			KEYPAD_PORT_DIR = (0b00010000 << Local_Col);
			//DIO_VoidSetPortValue(KEYPAD_PORT,(~(0b00010000<< Local_Col)));
			KEYPAD_PORT_OUT = (~(0b00010000<< Local_Col));

			for (Local_Row = 0; Local_Row < N_ROW; Local_Row++)
			{
				if (BIT_IS_CLEAR(KEYPAD_PORT_IN,Local_Row))
				{
					#if (N_COL == 3)

					return Keypad_4x3_adjustKeyNumber (((row*N_COL)+col+1));
					#elif (N_COL == 4)

					return Keypad_4x4_adjustKeyNumber (((Local_Row*N_COL)+Local_Col+1));

					#endif
				}
			}
		}
	}
}

#if (N_COL == 3)

static u8 Keypad_4x3_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
	case 10:
		return '*'; //	ASCII code of *
		break;
	case 11:
		return 0;
		break;
	case 12:
		return '#'; //	ASCII code of #
		break;
	default:
		return button_number;
		break;
	}
}


#elif (N_COL == 4)

u8 Keypad_4x4_adjustKeyNumber (u8 button_number)
{
	switch (button_number)
	{
	case 1:		return 'T';
				break;
	case 2:		return 8;
				break;
	case 3:		return 9;
				break;
	case 4:		return '/';
				break;
	case 5:		return 'L';
				break;
	case 6:		return 'O';
				break;
	case 7:		return 'F';
				break;
	case 8:		return '*';
				break;
	case 9:		return 'A';
				break;
	case 10:	return 'B';
				break;
	case 11:	return 'C';
				break;
	case 12:	return '-';
				break;
	case 13:	return 'c';
				break;
	case 14:	return 0;
				break;
	case 15:	return '=';
				break;
	case 16:	return '+';
				break;
	}
}

#endif
