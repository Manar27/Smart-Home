/*
 * LDR_interface.h
 *
 *  Created on: Sep 16, 2022
 *      Author: Manar
 */

#ifndef HAL_LDR_HEADER_LDR_INTERFACE_H_
#define HAL_LDR_HEADER_LDR_INTERFACE_H_

void LDR_VoidInit(void);
u32 LDR_u8GetValue(u8 ADC_channel, u32 Resistor_Value);

#endif /* HAL_LDR_HEADER_LDR_INTERFACE_H_ */
