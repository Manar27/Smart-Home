/*
  Author:  Mohamed Zaki
  Data:    17-8-2021
  Version: 1.00
*/

#ifndef HAL_KPD_HEADER_KPD_CONFIG_H_
#define HAL_KPD_HEADER_KPD_CONFIG_H_
#include "../../../MCAL/DIO/Header/DIO_Register.h"

#include "../../../MCAL/DIO/Header/DIO_interface.h"
/***************************************************************************************************/
/*****************************************Define Data Types*****************************************/

//	Keypad port Configuration
#define KEYPAD_PORT_DIR		DIO_DDRA
#define KEYPAD_PORT_OUT		DIO_PORTA
#define KEYPAD_PORT_IN		DIO_PINA
//	Keypad Configuration for Rows & ColumnS
#define	N_ROW 4
#define N_COL 4

#define ROWStart	0
#define ROWEnd		3

#define ColumnStart	4
#define ColumnEnd	7

#endif
