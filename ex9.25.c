/* a switch is connected to pin P1.2 write a code
 * to monitor SW and create the following on pun P1.7:
 * SW = 0: 500hz
 * SW = 1: 750hz, use timer 0, mode 1 for both of them
 */
#include <reg51.h>
#include <stdio.h>

sbit mybit = P1^7;      /* mybit being wave */
sbit SW = P1^2;
void TOM1Delay(unsigned char);

void main(){

    SW = 1;
    while (1){
        mybit =~ mybit;
        if (SW == 0)
            TOM1Delay(0);
        else
            TOM1Delay(1);
    }
}

void TOM1Delay(unsigned char c){
    TMOD = 0x01;
    if (c == 0){
        TL0 = 0x67;
        TH0 = 0xFC;
    }
    else{
        TL0 = 0x9A;
        TH0 = 0xFD;
    }
    TR0 = 1;
    while(TF0 == 0){
        /* till the flag is 0 */

        ;
    }
    TR0 = 0;
    TF0 = 0;
}

/* note;
 * SW = 1; (to make any pin as input pin)
 * (timer -- def'n)
 * 1) T0 -- TH0, TL0; T1 -- Th1, Tl1
 * 2) gotta load the val. & set TR = 1;
 *
 * F = 500hz T = 1/500 = 1.085usec
 * according to that the values are set in the reg.
 */
