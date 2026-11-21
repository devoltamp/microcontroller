/* interfaced DAC, that produces a triangular wave of peak 1v */
#include <reg51.h>

/* precalculated values from:
 * V_dac(i/p) = 2.56 * n                  (for n = 0 to 9)
 * V_dac(i/p) = 25.6 - 2.56 * (n - 10)    (for n = 10 to 19)
 */
code unsigned char signal[20] = {
     0,  2,  5,  7, 10, 12, 15, 17, 20, 23,
    25, 23, 20, 17, 15, 12, 10,  7,  5,  2

    /* rounded values
     * 0, 3, 5, 8, 10, 13, 15, 18, 20, 23
     * 26, 23, 20, 18, 15, 13, 10, 8, 5, 3
     */
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
