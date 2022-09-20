/*
 * Bit_math.h
 *
 *  Created on: Aug 8, 2022
 *      Author: Manar
 */

#ifndef COMMON_BIT_MATH_H_
#define COMMON_BIT_MATH_H_

#define Set_Bit(Reg,Bit) 		Reg |= (1<<Bit)
#define toggle_Bit(Reg,Bit)  	Reg ^= (1<<Bit)
#define clear_Bit(Reg,Bit) 		Reg &=~ (1<<Bit)
#define Get_Bit(Reg,Bit)		(Reg >> Bit) & 1
#define BIT_IS_CLEAR(REG_Name,PIN_NO) (!(REG_Name & (1<<PIN_NO)))	//Macro to check if certain bit is clear

/*prototypes*/
/*void Set_Bit (u8 Reg, u8 Bit);
void toggle_Bit (u8 Reg, u8 Bit);
void clear_Bit (u8 Reg, u8 Bit);
u8 Get_Bit (u8 Reg, u8 Bit);*/

#endif /* COMMON_BIT_MATH_H_ */
