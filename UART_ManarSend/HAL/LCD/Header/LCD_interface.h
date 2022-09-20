/*
 * LCD_interface.h
 *
 *  Created on: Aug 11, 2022
 *      Author: Manar
 */

#ifndef HAL_LCD_HEADER_LCD_INTERFACE_H_
#define HAL_LCD_HEADER_LCD_INTERFACE_H_

#include "LCD_Private.h"

void LCD_Void8BitInit(void);
void LCD_VoidSendCommand(u8 Local_command);
void LCD_VoidSendChar(u8 Local_char);
void LCD_VoidSendString(char *Ref_string);
void LCD_VoidStartFrom(u8 Local_RowPosition, u8 Local_ColPosition);
void LCD_VoidSendNumber(u32 Local_Number);
void LCD_VoidSendStringFromPos (char *Ref_string, u8 Local_RowPosition, u8 Local_ColPosition);
void LCD_VoidAddCustomPattern(u8 * Local_Pattern, u8 Local_IndexCGRAM);
void LCD_VoidCustomDisplay(u8 Local_CGRAMIndex, u8 Local_RowPosition, u8 Local_ColPosition);
//void LCD_VoidRightShift (u8 Local_shiftNumbers);
/*CGRAM & CGROM*/

#endif /* HAL_LCD_HEADER_LCD_INTERFACE_H_ */
