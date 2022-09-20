/*
 * DCM_Interface.h
 *
 *  Created on: Sep 1, 2022
 *      Author: manar
 */

#ifndef HAL_DCM_HEADER_DCM_INTERFACE_H_
#define HAL_DCM_HEADER_DCM_INTERFACE_H_

#define DCM_Start 1
#define DCM_Stop  0

void DCM_VoidInitSingleControl (u8 Local_State);
void DCM_VoidInitHBridge (void);
void DCM_VoidRotateCW (void);
void DCM_VoidRotateCCW (void);
void DCM_VoidStop (void);

#endif /* HAL_DCM_HEADER_DCM_INTERFACE_H_ */
