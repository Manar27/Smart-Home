/*
 * LDR_Prog.c
 *
 *  Created on: Sep 16, 2022
 *      Author: Manar
 */
#include "../../../Common/Bit_math.h"
#include "../../../Common/typedef.h"
#include "../../../Common/Macro's.h"

#include "../../../MCAL/ADC/Header/ADC_interface.h"
#include "../Header/LDR_interface.h"

void LDR_VoidInit(void)
{
	ADC_VoidInitPolling();
}
u32 LDR_u8GetValue(u8 ADC_channel, u32 Resistor_Value)
{
	u16 ADC_Reading = ADC_U16GetValue(ADC_channel);
	u16 Analog_Volt = (ADC_Reading * 5000)/1024;
	//u16 LDR_Value = Analog_Volt * 3.8;
	u32 LDR_Value = (Analog_Volt*Resistor_Value)/(5 - Analog_Volt);
	return LDR_Value;
}
