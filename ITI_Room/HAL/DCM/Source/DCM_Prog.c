/*
 * DCM_Prog.c
 *
 *  Created on: Sep 1, 2022
 *      Author: Manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"
#include "../../../MCAL/DIO/Header/DIO_interface.h"

#include "../Header/DCM_Config.h"
#include "../Header/DCM_Interface.h"

void DCM_VoidInitSingleControl (u8 Local_State)
{
	DIO_VoidSetPinDir(DCM_BridgeGroup,DCM_SingleControlPin,Output);

	if (Local_State == DCM_Start)
	{
		DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_SingleControlPin,High);
	}
	else if (Local_State == DCM_Stop)
	{
		DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_SingleControlPin,Low);
	}
}
void DCM_VoidInitHBridge (void)
{
	DIO_VoidSetPinDir(DCM_BridgeGroup,DCM_Tran1,Output);
	DIO_VoidSetPinDir(DCM_BridgeGroup,DCM_Tran2,Output);
	DIO_VoidSetPinDir(DCM_BridgeGroup,DCM_Tran3,Output);
	DIO_VoidSetPinDir(DCM_BridgeGroup,DCM_Tran4,Output);
}
void DCM_VoidRotateCW (void)
{
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran1,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran4,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran2,High);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran3,High);
}
void DCM_VoidRotateCCW (void)
{
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran2,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran3,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran1,High);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran4,High);
}
void DCM_VoidStop (void)
{
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran1,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran2,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran3,Low);
	DIO_VoidSetPinValue(DCM_BridgeGroup,DCM_Tran4,Low);
}
