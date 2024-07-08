/*
 * UART_CFG.h
 *
 * Created: 7/6/2024 8:51:39 PM
 *  Author: khaled
 */ 


#ifndef UART_CFG_H_
#define UART_CFG_H_

/************************************************************************/
/*                       UBRR------>(0 - 4095)                          */
/*             normal speed -------> UBRR=(Focs/(16*BOUD))-1            */
/*                double speed -------> UBRR=(Focs/(8*BOUD))-1          */
/************************************************************************/
#define UBRR_VAL		51//BOUD RATE 9600


//speed modes
#define NORMAL_SPEED	0
#define DOUBLE_SPEED		1

//select speed mode
#define UART_SPEED_MODE		NORMAL_SPEED

#endif /* UART_CFG_H_ */