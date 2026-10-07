/* interfaced DAC, that produces a shifted sine wave of peak 1v */
#include <reg51.h>

/* do the calculation one more time */
code unsigned char signal[20] = {
    25, 33, 40, 46, 49, 51, 49, 46, 40, 33,
    25, 17, 10,  4,  1,  0,  1,  4, 10, 17
};
volatile unsigned char n = 0;

/* †(2) */
void tmr0_isr() interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x18;

    P2 = signal[n];     /* giving the values */
    n++;
    if (n >= 20){
        n = 0;
    }
    /* reset sample index */
}

void main(){

    TMOD = 0x01;
    TH0 = 0xFC;     /* for 1ms */
    TL0 = 0x18;

    ET0 = 1;        /* enable timer 0 */
    EA = 1;
    TR0 = 1;

    P2 = 0x00;      /* as o/p */
    while(1){
        ;
    }
}

/* notes;
 *
 * †(1)
 * here, using the loop to calculate the dac o/p is just gonna use the
 * time, ram & rom -- floating point calculation on 8 bit mc is not done.
 *
 * †(2)
 * #n to be loaded in timer 0, calculation;
 * 65536 - 1000 = 64536 = 0xFC18
*/
