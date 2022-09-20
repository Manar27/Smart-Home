/*
 * ADC_Prog.c
 *
 *  Created on: Aug 22, 2022
 *      Author: manar
 */
#include "../../../Common/typedef.h"
#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"

#include "../../DIO/Header/DIO_interface.h"
#include "../Header/ADC_Register.h"
#include "../Header/ADC_Private.h"
#include "../Header/ADC_Config.h"
#include "../Header/ADC_interface.h"

void ADC_VoidInitPolling	(void)
{
	/*enable ADC*/
	Set_Bit(ADC_ADCSRA, ADC_ADEN);
	/*Set reference voltage to AVCC*/
	Set_Bit(ADC_ADMUX, ADC_REFS0);
	clear_Bit(ADC_ADMUX, ADC_REFS1);
	/*deactivate left adjust result*/
	clear_Bit(ADC_ADMUX,ADC_ADLAR);
	/*Select prescaler to 32 --> 011*/
	Set_Bit(ADC_ADCSRA, ADC_ADPS0);
	Set_Bit(ADC_ADCSRA, ADC_ADPS1);
	Set_Bit(ADC_ADCSRA, ADC_ADPS2);

}
void ADC_VoidInitInterrupt	(void)
{
	/*enable ADC*/
	Set_Bit(ADC_ADCSRA, ADC_ADEN);
	/*Set reference voltage to AVCC*/
	Set_Bit(ADC_ADMUX, ADC_REFS0);
	clear_Bit(ADC_ADMUX, ADC_REFS1);
	/*activate left adjust result*/
	Set_Bit(ADC_ADMUX,ADC_ADLAR);
	/*Select prescaler to 8 --> 011*/
	Set_Bit(ADC_ADCSRA, ADC_ADPS0);
	Set_Bit(ADC_ADCSRA, ADC_ADPS1);
	clear_Bit(ADC_ADCSRA, ADC_ADPS2);
}

u16 ADC_U16GetValue(u8 ADC_Channel)
{
	u16 LOCAL_READ ;
	/*Select THe 5 Bit */
	ADC_Channel  = ADC_Channel & 0x1F;
	ADC_ADMUX  &= 0xE0 ;
	ADC_ADMUX  |= ADC_Channel ;
	/*Start conversion*/
	ADC_ADCSRA |= (1<<ADC_ADSC);
	while((Get_Bit(ADC_ADCSRA,ADC_ADIF)) == 0);
	LOCAL_READ = ADC_ADCW;
	return LOCAL_READ;

}
