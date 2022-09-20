/*
 * Timer0_Interface.h
 *
 *  Created on: Aug 23, 2022
 *      Author: manar
 */

#ifndef MCAL_TIMER0_HEADER_TIMER0_INTERFACE_H_
#define MCAL_TIMER0_HEADER_TIMER0_INTERFACE_H_

void Timer0_VoidInitNormal (u8 Local_PreLoad);
void Timer0_VoidInitCTC (u8 Local_CompareValue);

void Timer0_VoidPWMSet (u8 Local_DutyCycle);

void Timer0_VoidSetPreload(u8 Local_Preload);

void Timer0_CallBackFunctionNormal(void (*PTF)(void));
void Timer0_CallBackFunctionCTC(void (*PTF)(void));

void __vector_11(void)		__attribute__((signal));
void __vector_10(void)		__attribute__((signal));

#endif /* MCAL_TIMER0_HEADER_TIMER0_INTERFACE_H_ */
