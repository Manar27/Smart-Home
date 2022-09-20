/*
 * DIO_interface.h
 *
 *  Created on: Aug 8, 2022
 *      Author: Manar
 */

#ifndef MCAL_DIO_HEADER_DIO_INTERFACE_H_
#define MCAL_DIO_HEADER_DIO_INTERFACE_H_

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/DIO_Private.h"

void DIO_VoidSetPinDir(u8 Local_Groupname, u8 Local_PinNumber, u8 Local_DirectionState);
void DIO_VoidSetPinValue(u8 Local_Groupname, u8 Local_PinNumber, u8 Local_valueState);
u8	 DIO_u8GetPinValue (u8 Local_Groupname, u8 Local_PinNumber);
void DIO_VoidSetPortDir(u8 Local_Groupname, u8 Local_DirectionState);
void DIO_VoidSetPortValue(u8 Local_Groupname, u8 Local_valueState);
u8	 DIO_u8GetPortValue (u8 Local_Groupname);
void DIO_VoidToggleBit(u8 Local_Groupname, u8 Pin);
void DIO_VoidTogglePORT(u8 Local_Groupname);


#endif /* MCAL_DIO_HEADER_DIO_INTERFACE_H_ */
