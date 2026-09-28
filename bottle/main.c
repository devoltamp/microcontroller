#include <reg51.h>

sbit MOTOR = P0^2;

volatile unsigned int bottle_count = 0;
volatile unsigned int timer_tick_count = 0;

void delay_1_minute(void);

/* P3.2 */
void exo_isr(void) interrupt 0 {
    bottle_count++;
}

void tmr0_isr(void) interrupt 1 {
    TH0 = 0x4C;     /* 50ms delay @ 12MHz */
    TL0 = 0x00;

    timer_tick_count++;
}

void main(void) {

    TMOD = 0x01;    /* 16-bit timer */
    IE = 0x83;      /* 1000 0011 (EA | ET0 | EX0) */
    IT0 = 1;        /* edge tri. */

    MOTOR = 1;

    while(1) {
        if (bottle_count >= 100) {
            MOTOR = 0;           /* stop */
            delay_1_minute();
            bottle_count = 0;    /* reset bottle counter */
            MOTOR = 1;           /* restart the belt */
        }
    }
}

void delay_1_minute(void) {
    /* 50 ms delay = 1200 ticks for 60 seconds (1200 * 50 ms = 60,000 ms) - more explained in the link */
    timer_tick_count = 0;

    TH0 = 0x4C;
    TL0 = 0x00;

    TR0 = 1;
    /* wait for the tick completion */
    while(timer_tick_count < 1200);
    TR0 = 0;
}

/* note;
 *
 * †(1)
 * Configure Interrupt Control Registers
 * IE (Interrupt Enable Register):
 * EA = 1 (Enable all interrupts)
 * EX0 = 1 (Enable External Interrupt 0)
 * ET0 = 1 (Enable Timer 0 Interrupt)
 * -- whole thing is written as 0x83 - noice
 *
 * †(2)
 * for the one minute time delay;
 * https://share.gemini.google/vhYupn29VzN3
 */
