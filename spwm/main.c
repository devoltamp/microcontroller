/* Interfaced Single-Phase SPWM Inverter using Timer 0 & Timer 1 (8051) */
#include <reg51.h>

sbit PWM_POS = P1^0;    /* Positive half-cycle SPWM output (0 to 10 ms) */
sbit PWM_NEG = P1^1;    /* Negative half-cycle SPWM output (10 to 20 ms) */

/* Precalculated Timer 0 reload values: 65536 - 350 * |sin(2 * pi * 50 * t)|
 * 40 samples at Ts = 0.5 ms (2 kHz switching for 50 Hz fundamental)
 */
code unsigned int load_count[40] = {
    /* Positive half-cycle (i = 0 to 19, t = 0.0 to 9.5 ms) */
    65536, 65481, 65428, 65377, 65330, 65289, 65253, 65224, 65203, 65190,
    65186, 65190, 65203, 65224, 65253, 65289, 65330, 65377, 65428, 65481,

    /* Negative half-cycle (i = 20 to 39, t = 10.0 to 19.5 ms) */
    65536, 65481, 65428, 65377, 65330, 65289, 65253, 65224, 65203, 65190,
    65186, 65190, 65203, 65224, 65253, 65289, 65330, 65377, 65428, 65481
};

volatile unsigned char i = 0;

/* Timer 0 ISR: Fires when ON-time (t_on) expires -> turns PWM OFF */
void tmr0_isr(void) interrupt 1 {
    TR0 = 0;            /* Stop Timer 0 until next switching period */
    PWM_POS = 0;
    PWM_NEG = 0;
}

/* Timer 1 ISR: Fires every Ts = 0.5 ms (2 kHz) -> starts next PWM pulse */
void tmr1_isr(void) interrupt 3 {
    unsigned int val;

    /* 1. Reload Timer 1 for next 0.5 ms switching period (65536 - 500 = 0xFE0C) */
    TH1 = 0xFE;
    TL1 = 0x0C;

    /* 2. Turn ON the appropriate H-bridge leg (skip if duty cycle == 0) */
    val = load_count[i];
    if (val < 65535) {
        TH0 = (unsigned char)(val >> 8);
        TL0 = (unsigned char)(val & 0xFF);

        if (i < 20) {
            PWM_POS = 1;
            PWM_NEG = 0;
        } else {
            PWM_POS = 0;
            PWM_NEG = 1;
        }
        TR0 = 1;        /* Start Timer 0 to time t_on */
    } else {
        PWM_POS = 0;
        PWM_NEG = 0;
    }

    /* 3. Advance sample index (0 to 39) */
    i++;
    if (i >= 40) {
        i = 0;
    }
}

void main(void) {
    PWM_POS = 0;
    PWM_NEG = 0;

    TMOD = 0x11;        /* Timer 1 = Mode 1 (16-bit), Timer 0 = Mode 1 (16-bit) */

    TH1 = 0xFE;         /* Initial Timer 1 reload for 0.5 ms */
    TL1 = 0x0C;

    ET0 = 1;            /* Enable Timer 0 interrupt */
    ET1 = 1;            /* Enable Timer 1 interrupt */
    EA  = 1;            /* Enable global interrupts */

    TR1 = 1;            /* Start Timer 1 carrier */

    while (1) {
        ;
    }
}
