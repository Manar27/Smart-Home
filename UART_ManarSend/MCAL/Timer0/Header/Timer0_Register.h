/*
 * Timer0_Register.h
 *
 *  Created on: Aug 23, 2022
 *      Author: manar
 */

#ifndef MCAL_TIMER0_HEADER_TIMER0_REGISTER_H_
#define MCAL_TIMER0_HEADER_TIMER0_REGISTER_H_

#define Timer0_OCR0			(*(volatile u8*)0x5C)
#define Timer0_TIMSK 		(*(volatile u8*)0x59)
#define Timer0_TIFR			(*(volatile u8*)0x58)
#define Timer0_TCNT0 		(*(volatile u8*)0x52)
#define Timer0_TCCR0 		(*(volatile u8*)0x53)

/*Control enable timer and read flag for Normal mood*/
#define Timer0_TOIE0		0
#define Timer0_TOV0			0
/*Control enable timer and read flag for CTC mood*/
#define Timer0_OCIE0		1
#define Timer0_OCF0			1
/*select mood*/
#define Timer0_WGM00 		6
#define Timer0_WGM01 		3
/*select the output on OC0 pin*/
#define Timer0_COM01 		5
#define Timer0_COM00 		4
/*select prescaler*/
#define Timer0_CS02 		2
#define Timer0_CS01 		1
#define Timer0_CS00 		0






#endif /* MCAL_TIMER0_HEADER_TIMER0_REGISTER_H_ */
