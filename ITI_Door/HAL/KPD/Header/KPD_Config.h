/*
 * KPD_Config.h
 *
 *  Created on: Aug 22, 2022
 *      Author: Manar
 */

#ifndef HAL_KPD_HEADER_KPD_CONFIG_H_
#define HAL_KPD_HEADER_KPD_CONFIG_H_

#include "../../../MCAL/DIO/Header/DIO_Register.h"
#include "../../../MCAL/DIO/Header/DIO_interface.h"

/*Keypad port Configuration*/
#define KEYPAD_PORT_DIR		DIO_DDRA
#define KEYPAD_PORT_OUT		DIO_PORTA
#define KEYPAD_PORT_IN		DIO_PINA

/*Keypad Configuration for Rows & Columns*/
#define	N_ROW 4
#define N_COL 4

#define ROWStart	0
#define ROWEnd		3

#define ColumnStart	4
#define ColumnEnd	7

#endif /*HAL_KPD_HEADER_KPD_CONFIG_H_*/
