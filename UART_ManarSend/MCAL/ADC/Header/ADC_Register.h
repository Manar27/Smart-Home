/*
 * ADC_Register.h
 *
 *  Created on: Aug 22, 2022
 *      Author: manar
 */

#ifndef MCAL_ADC_HEADER_ADC_REGISTER_H_
#define MCAL_ADC_HEADER_ADC_REGISTER_H_

#define ADC_ADMUX 	(*(volatile u8*)0x27)
#define ADC_ADCSRA 	(*(volatile u8*)0x26)
#define ADC_ADCH 	(*(volatile u8*)0x25)
#define ADC_ADCL 	(*(volatile u8*)0x24)
#define ADC_ADCW 	(*(volatile u16*)0x24)

#define ADC_REFS1	7
#define ADC_REFS0	6
#define ADC_ADLAR	5
#define ADC_MUX4	4
#define ADC_MUX3	3
#define ADC_MUX2	2
#define ADC_MUX1	1
#define ADC_MUX0	0

#define ADC_ADEN	7
#define ADC_ADSC	6
#define ADC_ADATE	5
#define ADC_ADIF	4
#define ADC_ADIE	3
#define ADC_ADPS2	2
#define ADC_ADPS1	1
#define ADC_ADPS0	0

#endif /* MCAL_ADC_HEADER_ADC_REGISTER_H_ */
