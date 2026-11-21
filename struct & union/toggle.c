/* toggle P1.0 every 1500 µs using timer 0 & struct/union */
#include <reg51.h>

sbit LED_PIN = P1^0;

union joshi {
    unsigned int j;
    struct jivan {
        unsigned char j1;   /* High byte (TH0) */
        unsigned char j2;   /* Low byte  (TL0) */
    } x;
} reg_x;

void tmr0_isr(void) interrupt 1 {
    TH0 = reg_x.x.j1;       /* Reload high byte (0xFA) */
    TL0 = reg_x.x.j2;       /* Reload low byte  (0x24) */
    LED_PIN = ~LED_PIN;     /* Toggle P1.0 every 1500 us */
}

void main(void) {
    reg_x.j = 0xFA24;       /* 65536 - 1500 = 64036 (0xFA24) */

    TMOD = 0x01;            /* Timer 0, Mode 1 (16-bit timer) */
    TH0  = reg_x.x.j1;      /* Load high byte */
    TL0  = reg_x.x.j2;      /* Load low byte */

    ET0 = 1;                /* Enable Timer 0 interrupt */
    EA  = 1;                /* Enable global interrupts */
    TR0 = 1;                /* Start Timer 0 */

    while (1) {
        ;
    }
}
