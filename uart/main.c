/* transmit string & echo received character */
#include <reg51.h>

void uart_init(void) {
    TMOD = 0x20;    /* Timer 1, Mode 2 (8-bit auto-reload) */
    TH1  = 0xFD;    /* 9600 baud rate @ 11.0592 MHz */
    SCON = 0x50;    /* Mode 1 (8-bit UART), REN = 1 */
    TR1  = 1;       /* Start Timer 1 */
}

void uart_tx(unsigned char ch) {
    SBUF = ch;          /* Load byte into transmit buffer */
    while (TI == 0);    /* Wait until transmission completes */
    TI = 0;             /* Clear transmit interrupt flag */
}

unsigned char uart_rx(void) {
    while (RI == 0);    /* Wait until a byte arrives */
    RI = 0;             /* Clear receive interrupt flag */
    return SBUF;        /* Return received byte */
}

void uart_tx_str(char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}

void main(void) {
    unsigned char rx_data;
    uart_init();
    uart_tx_str("8051 UART Ready\r\n");

    while (1) {
        rx_data = uart_rx();    /* Receive character */
        uart_tx(rx_data);       /* Echo back */
    }
}
