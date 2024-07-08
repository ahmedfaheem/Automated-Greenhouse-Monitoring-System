


#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_


void UART_Init(void);

void UART_Send(u8 data);

u8 UART_Receive(void);

u8 UART_ReceivePerodic(u8*pdata);



void UART_RX_InterruptEnable(void);
void UART_RX_InterruptDisable(void);

void UART_TX_InterruptEnable(void);
void UART_TX_InterruptDisable(void);

void UART_RX_SetCallBack(void (*LocalFptr)(void));
void UART_TX_SetCallBack(void (*LocalFptr)(void));


//enable globel interrupt
# define sei()  __asm__ __volatile__ ("sei" ::)

#endif /* UART_INTERFACE_H_ */