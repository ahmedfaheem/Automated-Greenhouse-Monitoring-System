#include "StdTypes.h"
#include "MemMap.h"
#include "UART_Interface.h"
#include "UART_Cfg.h"
static void(*UART_RX_Fptr)(void)=NULLPTR;
static void(*UART_TX_Fptr)(void)=NULLPTR;

#include "plant_char.h"

void UART_Init(void)
{
	//baud rate set
	UBRRL=UBRR_VAL;
	UBRRH=(UBRR_VAL&0xff00);
	//normal speed
	#if UART_SPEED_MODE==NORMAL_SPEED
	CLR_BIT(UCSRA,U2X);
	#elif	UART_SPEED_MODE==DOUBLE_SPEED
	SET_BIT(UCSRA,U2X);
	#endif
	
	
	//frame (stop ,data ,parity) 1 STOP NO PARITY 8 DATA
	
	// ENABLE RX TX
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(!GET_BIT(UCSRA,UDRE));
	UDR=data;
}




u8 UART_Receive(void)
{
	while(!GET_BIT(UCSRA,RXC));
	return UDR;
}


u8 UART_ReceivePerodic(u8*pdata)
{
	if (GET_BIT(UCSRA,RXC))
	{
		
		*pdata=UDR;
		return 1;
	}
	return 0;
}



void UART_RX_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_RX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_TX_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_TX_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void))
{
		UART_TX_Fptr = LocalFptr;
}


ISR(UART_RX_vect)
{
	if (UART_RX_Fptr!=NULLPTR)
	{
		UART_RX_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if (UART_TX_Fptr!=NULLPTR)
	{
		UART_TX_Fptr();
	}
}
