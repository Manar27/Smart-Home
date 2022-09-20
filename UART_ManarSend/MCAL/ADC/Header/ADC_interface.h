/*
 * ADC_interface.h
 *
 *  Created on: Aug 22, 2022
 *      Author: manar
 */

#ifndef MCAL_ADC_HEADER_ADC_INTERFACE_H_
#define MCAL_ADC_HEADER_ADC_INTERFACE_H_
#include "../Header/ADC_Register.h"
#include "../Header/ADC_Private.h"

void ADC_VoidInitPolling	(void);
void ADC_VoidInitInterrupt	(void);
u16 ADC_u16ReadDataPolling (u8 Local_Channel);
u16 ADC_U16GetValue(u8 ADC_Channel);
void ADC_VoidCallBackFunction (void (*ADC_PTF)(void));
void __vector_16 (void) __attribute__((signal));

#endif /* MCAL_ADC_HEADER_ADC_INTERFACE_H_ */
