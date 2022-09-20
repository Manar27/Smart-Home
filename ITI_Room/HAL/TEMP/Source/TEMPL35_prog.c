/*
 * TEMPL35_prog.c
 *
 *  Created on: Aug 28, 2022
 *      Author: Manar
 */
#include "../../../Common/Bit_math.h"
#include "../../../Common/typedef.h"
#include "../../../Common/Macro's.h"

#include "../../../MCAL/ADC/Header/ADC_interface.h"
#include "../Header/TEMPL35_Interface.h"
void TEMPL35_VoidInit(void)
{
	ADC_VoidInitPolling();
}
u8 TEMPL35_u8GetTemp(u8 Local_Channel)
{
	u16 Digital_Volt = ADC_U16GetValue(Local_Channel);
	u16 Analog_volt = (u16)(((u32)Digital_Volt * 5000UL) / 1024);
	u8 Temprature = Analog_volt/10 ; //check about this equation
	return Temprature ;
}
