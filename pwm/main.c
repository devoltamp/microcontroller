#include <reg51.h>

sbit PWM_OUT = P1^0;

/* 50% duty cycle at 2 kHz (Ts = 500 us, Ton = 250 us @ 12 MHz crystal) */
#define T1_RELOAD_H  0xFE   /* 65536 - 500 = 65036 (0xFE0C) */
#define T1_RELOAD_L  0x0C
#define T0_RELOAD_H  0xFF   /* 65536 - 250 = 65286 (0xFF06) */
#define T0_RELOAD_L  0x06

/* Timer 0 ISR: ON-time (Ton) elapsed -> pull PWM pin LOW */
void tmr0_isr(void) interrupt 1 {
    TR0 = 0;        /* Stop Timer 0 until next period */
    PWM_OUT = 0;
}

/* Timer 1 ISR: Switching period (Ts = 0.5 ms) elapsed -> start next pulse */
void tmr1_isr(void) interrupt 3 {
    TH1 = T1_RELOAD_H;
    TL1 = T1_RELOAD_L;

    TH0 = T0_RELOAD_H;
    TL0 = T0_RELOAD_L;

    PWM_OUT = 1;    /* Drive PWM pin HIGH */
    TR0 = 1;        /* Start Timer 0 to time Ton */
}

void main(void) {
    PWM_OUT = 0;
    TMOD = 0x11;    /* Timer 1 = Mode 1 (16-bit), Timer 0 = Mode 1 (16-bit) */

    TH1 = T1_RELOAD_H;
    TL1 = T1_RELOAD_L;

    ET0 = 1;        /* Enable Timer 0 interrupt */
    ET1 = 1;        /* Enable Timer 1 interrupt */
    EA  = 1;        /* Enable global interrupts */

    TR1 = 1;        /* Start Timer 1 switching carrier */

    while (1) {
        ;
    }
}
