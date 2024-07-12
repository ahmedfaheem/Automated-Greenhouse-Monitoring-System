#ifndef USART_REG_H
#define USART_REG_H

#define UDR   *((volatile uint8*)0x2C)

#define UCSRA   *((volatile uint8*)0x2B)

#define UCSRA_RXC       7u
#define UCSRA_TXC       6u
#define UCSRA_UDRE      5u


#define UCSRB   *((volatile uint8*)0x2A)
#define UCSRB_RXCIE    7u
#define UCSRB_TXCIE    6u
#define UCSRB_RXEN     4u
#define UCSRB_TXEN     3u
#define UCSRB_UCSZ2    2u




#define  UCSRC    *((volatile uint8*)0x40)
#define  UCSRC_URSEL     7u
#define  UCSRC_UMSEL     6u
#define  UCSRC_UPM1      5u
#define  UCSRC_UPM0      4u
#define  UCSRC_USBS      3u
#define  UCSRC_UCSZ1     2u
#define  UCSRC_UCSZ0     1u
#define  UCSRC_UCPOL     0u

#define UBRRH      *((volatile uint8*)0x40)
#define UBRRL      *((volatile uint8*)0x29)


#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))


#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)


/* USART, Rx Complete */
#define UART_RX_vect			__vector_13
/* USART Data Register Empty */
#define UART_UDRE_vect			__vector_14
/* USART, Tx Complete */
#define UART_TX_vect			__vector_15

#endif
