/*
* UART_Service.c
*
* Created: 7/8/2024 1:04:49 AM
*  Author: khaled
*/
#include "StdTypes.h"
#include "UART_Interface.h"
#include "UART_Service.h"
void UART_SendNumber(u32 num)
{
	UART_Send((u8)num);
	UART_Send((u8)(num>>8));
	UART_Send((u8)(num>>16));
	UART_Send((u8)(num>>24));
}
u32 UART_ReceiveNumber(void)
{
	u32 num;
	u8 b1,b2,b3,b4;
	b1 = UART_Receive();
	b2 = UART_Receive();
	b3 = UART_Receive();
	b4 = UART_Receive();
	num = b1|(b2<<8)|((u32)b3<<16)|((u32)b4<<24);
	return num;
}