/*
 * LCD_Private.h
 *
 *  Created on: Aug 15, 2022
 *      Author: Manar
 */

#ifndef HAL_LCD_HEADER_LCD_PRIVATE_H_
#define HAL_LCD_HEADER_LCD_PRIVATE_H_

/* Bit	      Settings
 * I/D:       0 = Decrease cursor position		1 = Increment cursor position
 * D: 	      0 = Display off					1 = Display on
 * S:	      0 = No display shift				1 = Display shift
 * C: 	      0 = Cursor blink off				1 = Cursor blink on
 * B: 	      0 = Decrease cursor position		1 = Increment cursor position
 * S/C:	      0 = Move Cursor					1 = Don't Move
 * R/L:	      0 = Shift Left					1 = Shift Right
 * DL:	      0 = 4-Bit Interface				1 = 8-Bit Interface
 * N:	      0 = 1/8 or 1/11 Duty (1 Line)		1 = 1/16 Duty (2 Lines)
 * F:	      0 = 5x7 dots						1 = 5x11 dots
 * BF:	      0 = Can accept instruction		1 = Internal operation
 * */
/*---------------------------------------------------------------------------------------------------*/
/*Function Set
RS  R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
=== === === === === === === === === ===
 0   0   0   0   1   DL  N   F   *   *
*/
#define LCD_Set4Bit1Line5x8         0x20	//Set_4Mode_1Line5x8	//0b00100000
#define LCD_Set4Bit1Line5x11        0x24	//Set_4Mode_1Line5x11	//0b00100100
#define LCD_Set4Bit2Line5x8	     	0x28	//Set_4Mode_2Lines5x8	//0b00101000
#define LCD_Set4Bit2Line5x11        0x2C	//Set_4Mode_2Line5x11	//0b00101100
#define LCD_Set8Bit1line5x8			0x30	//Set_8Mode_1Line5x8	//0b00110000
#define LCD_Set8Bit1Line5x11    	0x34	//Set_8Mode_1Line5x11	//0b00110100
#define LCD_Set8Bit2Line5x8     	0x38	//Set_8Mode_2Lines5x8	//0b00111000
#define LCD_Set8Bit2Line5x11    	0x3C	//Set_8Mode_2Line5x11	//0b00111100
/*---------------------------------------------------------------------------------------------------*/
/*Display On Off Control command 00001DCB
 * 1- D = 1 --> Display On
 * 2- C = 1 --> Cursor On
 * 3- B = 0 --> Cursor Off
 * */
#define LCD_DisplayOFF   0x08  //0b0001000, D = 0    C = 0    B = 0    The Display is Off so Will Cursor is off  And Blinking is OFF
#define LCD_DisplayON    0x0C  //0b0001100, D = 1    C = 0    B = 0    The Display is On But the Cursor is OFF so the Blinking is OFF
#define LCD_CursorON     0x0E  //0b0001110
#define LCD_CURSOROFF	 0x0C

/*---------------------------------------------------------------------------------------------------*/
/*Clear Display*/
#define LCD_ClearDisplay     	  0x01			//0b00000001
/*---------------------------------------------------------------------------------------------------*/
/*Set CG RAM Address*/
#define  LCD_SetAddressCGRAM      0x40
/*---------------------------------------------------------------------------------------------------*/
/*Set DDRAM Address*/
#define  LCD_SetAddressDDRAM      0x80
/*---------------------------------------------------------------------------------------------------*/
/*Return Display to its original position 00h  0000001-*/
#define LCD_ReturnHome       0x02
/*---------------------------------------------------------------------------------------------------*/
/*Entry Mode Set*/
#define LCD_EntryMode2       0x06 //  S = 0 (no screen shifting) & I/D = 1 (Increment cursor position)   /*Increment cursor (shift cursor to right)*/
#define LCD_DisplayShift	 0x1C
#endif /* HAL_LCD_HEADER_LCD_PRIVATE_H_ */
