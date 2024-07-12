#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

void USART_voidInit();

void USART_voidTransmit(uint8 Copy_u8Data);

uint8 USART_u8Receive();

void UART_voidSendNumber(uint32 Copy_u32Number);

uint32 UART_u32ReceiveNumber(void);

void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));

#endif
