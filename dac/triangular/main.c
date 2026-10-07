/* broken */
#include <reg51.h>


code unsigned char signal[20] = {
    0,  5, 10, 15, 20, 26, 31, 36, 41, 46,
   51, 46, 41, 36, 31, 26, 20, 15, 10,  5
};
volatile unsigned char n = 0;


/* 1ms time interval */
void tmr0_isr() interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x18;

    P2 = signal[n];     /* o/p value to dac */
    n++;
    if (n >= 20) {
        n = 0;          /* reset the sample index */
    }
}

void main() {
    TMOD = 0x01;
    TH0  = 0xFC;
    TL0  = 0x18;

    ET0  = 1;
    EA   = 1;
    TR0  = 1;

    P2   = 0x00;
    while(1) {
        ;
    }
}

/* notes:
 *
 * †(1)
 * pre-calculating array in lookup table avoids execution of real-time floating-point
 * arithmetic in the 8051 ISR, saving processing overhead and memory.
 *
 * †(2)
 * timer 0 count calculation for 1ms @ 12 MHz:
 * 65536 - 1000 = 64536 = 0xFC18
 *
 * rest is pretty much the same as sine
 */
