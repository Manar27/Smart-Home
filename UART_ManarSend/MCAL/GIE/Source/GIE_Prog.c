/*
 * GIE_Prog.c
 *
 *  Created on: Aug 20, 2022
 *      Author: manar
 */

#include "../../../Common/Bit_math.h"
#include "../../../Common/Macro's.h"
#include "../../../Common/typedef.h"

#include "../Header/GIE_Register.h"
#include "../Header/GIE_interface.h"

void GIE_VoidEnable (void)
{
	Set_Bit(GIE_SREG,GIE_SREG_I);
}

void GIE_VoidDisable (void)
{
	clear_Bit(GIE_SREG,GIE_SREG_I);
}
