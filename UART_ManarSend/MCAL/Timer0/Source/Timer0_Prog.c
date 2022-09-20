/*
 * Timer0_Prog.c
 *
 *  Created on: Aug 23, 2022
 *      Author: manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/Timer0_Register.h"
#include "../Header/Timer0_Private.h"
#include "../Header/Timer0_Config.h"
#include "../Header/Timer0_Interface.h"

static void (*GPTF_Normal) (void) = NULL;
static void (*GPTF_CTC) (void) = NULL;

void Timer0_VoidInitNormal (u8 Local_PreLoad)
{
	Timer0_TCNT0 = Local_PreLoad;
	/*select normal mode*/
	clear_Bit(Timer0_TCCR0,Timer0_WGM01);
	clear_Bit(Timer0_TCCR0,Timer0_WGM00);
	/*Enable overflow interrupt*/
	Set_Bit(Timer0_TIMSK,Timer0_TOIE0);
#if Timer0_Prescaler == NoClkCource
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == NoPrescale
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler8
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler64
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler256
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler1024
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == ExternalClkFalling
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == ExternalClkRising
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);

#endif

#if OC0_Mode == OC0_Toggle
	Set_Bit(Timer0_TCCR0,Timer0_COM00);
	clear_Bit(Timer0_TCCR0,Timer0_COM01);
#elif OC0_Mode == OC0_Disconnected
	clear_Bit(Timer0_TCCR0,Timer0_COM00);
	clear_Bit(Timer0_TCCR0,Timer0_COM01);
#elif OC0_Mode == OC0_Clear
	clear_Bit(Timer0_TCCR0,Timer0_COM00);
	Set_Bit(Timer0_TCCR0,Timer0_COM01);
#elif OC0_Mode == OC0_Toggle
	Set_Bit(Timer0_TCCR0,Timer0_COM00);
	clear_Bit(Timer0_TCCR0,Timer0_COM01);
#endif
}
void Timer0_VoidInitCTC (u8 Local_CompareValue)
{
	Timer0_OCR0 = Local_CompareValue;
	/*Select CTC mode*/
	Set_Bit(Timer0_TCCR0,Timer0_WGM01);
	clear_Bit(Timer0_TCCR0,Timer0_WGM00);
	/*Enable interrupt on compare match*/
	Set_Bit(Timer0_TIMSK,Timer0_OCIE0);
#if Timer0_Prescaler == NoClkCource
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == NoPrescale
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler8
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler64
	clear_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler256
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == Prescaler1024
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	clear_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == ExternalClkFalling
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	clear_Bit(Timer0_TCCR0,Timer0_CS00);
#elif Timer0_Prescaler == ExternalClkRising
	Set_Bit(Timer0_TCCR0,Timer0_CS02);
	Set_Bit(Timer0_TCCR0,Timer0_CS01);
	Set_Bit(Timer0_TCCR0,Timer0_CS00);

#endif
}
void Timer0_VoidSetPreload(u8 Local_Preload)
{
	Timer0_TCNT0 = Local_Preload;
}
void Timer0_CallBackFunctionNormal(void (*PTF)(void))
{
	GPTF_Normal = PTF;
}
void Timer0_CallBackFunctionCTC(void (*PTF)(void))
{
	GPTF_CTC = PTF;
}

void __vector_11(void)
{
	GPTF_Normal();
}
void __vector_10(void)
{
	GPTF_CTC();
}
