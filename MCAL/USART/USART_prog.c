#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "USART_interface.h"
#include "USART_reg.h"
#include "USART_cfg.h"
#include "USART_prv.h"


void USART_voidInit(){

	uint8 Local_u8UCSRCValue = 0u;
	/*  Select register to UCSRC */
	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);

	/*set 8bit mode*/
	CLR_BIT(UCSRB, UCSRB_UCSZ2);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);

	/*set USART Mode Select to Asynchronous*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UMSEL);
	/*disable parity*/
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM0);
	CLR_BIT(Local_u8UCSRCValue,UCSRC_UPM1);
	/*stop bit 1*/
	CLR_BIT(Local_u8UCSRCValue, UCSRC_USBS);
  /*add final value to register (can not use set and clr because select reg must be on same operation)*/
    UCSRC = Local_u8UCSRCValue;

    /*set baud rate  9600bps with 16Mhz oscillator  frequency*/
	UBRRL  = 103;

	/*Enable transmit and receiver */
	SET_BIT(UCSRB, UCSRB_TXEN);
	SET_BIT(UCSRB, UCSRB_RXEN);

}

void USART_voidTransmit(uint8 Copy_u8Data){

	/* wait until UDRE is empty */
	while(GET_BIT(UCSRA,UCSRA_UDRE) == 0);
	UDR = Copy_u8Data;
}

uint8 USART_u8Receive(){

	/* wait until the data received */
	while(GET_BIT(UCSRA,UCSRA_RXC) == 0);

	return UDR;

}


void UART_voidSendNumber(uint32 Copy_u32Number){
	USART_voidTransmit((uint8)Copy_u32Number);
	USART_voidTransmit((uint8)(Copy_u32Number>>8));
	USART_voidTransmit((uint8)(Copy_u32Number>>16));
	USART_voidTransmit((uint8)(Copy_u32Number>>24));
}

uint32 UART_u32ReceiveNumber(void){
	
		uint32 Copy_u32Number;
	uint8 b1,b2,b3,b4;
	b1 = USART_u8Receive();
	b2 = USART_u8Receive();
	b3 = USART_u8Receive();
	b4 = USART_u8Receive();
	Copy_u32Number = b1|(b2<<8)|((uint32)b3<<16)|((uint32)b4<<24);
	return Copy_u32Number;
}
