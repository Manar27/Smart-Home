/*
 * LED_interface.h
 *
 *  Created on: Aug 14, 2022
 *      Author: Manar
 */

#ifndef HAL_LED_HEADER_LED_INTERFACE_H_
#define HAL_LED_HEADER_LED_INTERFACE_H_

void LED_VoidInit(void);
void LED_VoidTurnOffAll(void);
void LED_VoidTurnOnAll(void);
void LED_VoidToggleAll(void);

void LED_VoidTurnOnOne(u8 Local_LED_number);
void LED_VoidTurnOffOne(u8 Local_LED_number);
void LED_VoidToggleOne(u8 Local_LED_number);

void LED_VoidTurnOnRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);
void LED_VoidTurnOnLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);

void LED_VoidTurnOffRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);
void LED_VoidTurnOffLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);

void LED_VoidToggleRightGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);
void LED_VoidToggleLeftGroup(u8 Local_LED_number, u8 Local_NumberOfLEDs);

#endif /* HAL_LED_HEADER_LED_INTERFACE_H_ */
